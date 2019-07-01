#include "mqttInterface.h"
#include "mqtt_internal.h"
#include "usart.h"


const char clientID[] = "12345|securemode=3,signmethod=hmacsha1|";
const char password[] = "75F3DE81150DC154D09DAA64E588B97BCC45BA20";
const char username[] = "device&a1zPE6uuzgg";	

unsigned char MQTTSendBuf[1024];
unsigned char MQTTReciBuf[1024];


// 阿里云连接ack
int AliRecv_CONNACK(uint16_t len)
{
	int rc = SUCCESS_RETURN;
	unsigned char connack_rc = 255;
  char sessionPresent = 0;
	
	if (MQTTDeserialize_connack((unsigned char *)&sessionPresent, &connack_rc, (unsigned char *)MQTTReciBuf,
															len) != 1) {
			return MQTT_CONNECT_ACK_PACKET_ERROR;
	}
			
	    switch (connack_rc) {
        case IOTX_MC_CONNECTION_ACCEPTED:
            rc = SUCCESS_RETURN;
            break;
        case IOTX_MC_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION:
            rc = MQTT_CONANCK_UNACCEPTABLE_PROTOCOL_VERSION_ERROR;
            break;
        case IOTX_MC_CONNECTION_REFUSED_IDENTIFIER_REJECTED:
            rc = MQTT_CONNACK_IDENTIFIER_REJECTED_ERROR;
            break;
        case IOTX_MC_CONNECTION_REFUSED_SERVER_UNAVAILABLE:
            rc = MQTT_CONNACK_SERVER_UNAVAILABLE_ERROR;
            break;
        case IOTX_MC_CONNECTION_REFUSED_BAD_USERDATA:
            rc = MQTT_CONNACK_BAD_USERDATA_ERROR;
            break;
        case IOTX_MC_CONNECTION_REFUSED_NOT_AUTHORIZED:
            rc = MQTT_CONNACK_NOT_AUTHORIZED_ERROR;
            break;
        default:
            rc = MQTT_CONNACK_UNKNOWN_ERROR;
            break;
    }

    return rc;
}

// mqtt 连接到阿里云
int AliMQTTConnect(void) 
{

	MQTTPacket_connectData connectdata = MQTTPacket_connectData_initializer;
	int len = 0;
	
	// 参数初始化
	connectdata.cleansession = 1;
	connectdata.clientID.cstring  = (char *)clientID;
	connectdata.keepAliveInterval = 60;
	connectdata.MQTTVersion = IOTX_MC_MQTT_VERSION;
	connectdata.username.cstring = (char *)username;
	connectdata.password.cstring = (char *)password;

	// 打包阿里数据
	if ((len = MQTTSerialize_connect(MQTTSendBuf, sizeof(MQTTSendBuf), &connectdata)) <= 0) {
        return MQTT_CONNECT_PACKET_ERROR;
  }
	
	// 循环发送一帧阿里云数据
	while(1) 
	{
		MQTTsendPacketBuffer(MQTTSendBuf,len);
		int len = MQTTgetData(MQTTReciBuf,sizeof(MQTTReciBuf),2000);
		
		// 接受到一帧数据
		if(len != -1) 
		{
			// 响应正确
			if(AliRecv_CONNACK(len) == SUCCESS_RETURN) 
			{
				break;
			}
		}

		HAL_Delay(5000);
	}
	
	
	return SUCCESS_RETURN;
}


void message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    iotx_mqtt_topic_info_t     *topic_info = (iotx_mqtt_topic_info_pt) msg->msg;

    switch (msg->event_type) {
        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
//            /* print topic name and topic message */
//            EXAMPLE_TRACE("Message Arrived:");
//            EXAMPLE_TRACE("Topic  : %.*s", topic_info->topic_len, topic_info->ptopic);
//            EXAMPLE_TRACE("Payload: %.*s", topic_info->payload_len, topic_info->payload);
//            EXAMPLE_TRACE("\n");
            break;
        default:
            break;
    }
}

// 订阅示例

uint16_t packetid = 0;
void subscribeExample(void)
{
    int len = 0;
		MQTTString topic = MQTTString_initializer;
		int qos = IOTX_MQTT_QOS0;
		
    topic.cstring = "/a1zPE6uuzgg/device/user/get";

	
		// 打包订阅数据
    len = MQTTSerialize_subscribe(MQTTSendBuf,sizeof(MQTTSendBuf),0,++packetid,1,&topic,&qos);
		
	// 发送订阅消息
		MQTTsendPacketBuffer(MQTTSendBuf,len);
	// 等待订阅消息返回
		len = MQTTgetData(MQTTReciBuf,sizeof(MQTTReciBuf),2000);
}



// 发送示例
void publishExample(void)
{
	int len = 0;
	char payload[] = "{params:{counter:20}}";
	int qos = IOTX_MQTT_QOS0;
	MQTTString topic = MQTTString_initializer;
	topic.cstring = "/sys/a1zPE6uuzgg/device/thing/event/property/post";
//	topic.cstring = "/a1zPE6uuzgg/device/user/update";
	

	// 打包发送数据
	len = MQTTSerialize_publish(MQTTSendBuf,sizeof(MQTTSendBuf),0,qos,0,0,topic,(unsigned char *)payload,strlen(payload));
	MQTTsendPacketBuffer(MQTTSendBuf,len);
}


// 接受一帧publish数据
iotx_mqtt_topic_info_t topic_msg;
void recv_PUBLISH(uint16_t len) 
{
	int result = 0;
	MQTTString topicName;
	int qos = 0;
	uint32_t payload_len = 0;
	
	if(1 != MQTTDeserialize_publish((unsigned char *)&topic_msg.dup,
                                     (int *)&qos,
                                     (unsigned char *)&topic_msg.retain,
                                     (unsigned short *)&topic_msg.packet_id,
                                     &topicName,
                                     (unsigned char **)&topic_msg.payload,
                                     (int *)&payload_len,
                                     (unsigned char *)U1ReciMessage.ReciBuf,
                                     len)){
				while(1);							 
	}
																		 
	topic_msg.qos = (unsigned char)qos;
  topic_msg.payload_len = payload_len;
}


// 接受处理 MQTT_Yield
void Ali_MQTT_Yield(void)
{
	unsigned int packetType;
	MQTTHeader header = {0};
	
	uint16_t reciLen = 0;
	unsigned short mypacketid;
	int grantedQoS[MUTLI_SUBSCIRBE_MAX];
	int rc,count = 0;
	
	
	// 接收到一帧数据
	if(U1ReciMessage.ReciDispose) {
		reciLen = U1ReciMessage.MessageLen;
		U1ReciMessage.MessageLen = 0;
		U1ReciMessage.ReciDispose = false;
		
		if(reciLen < 2) {
			return;
		}
		
		// 得到接受包类型
		header.byte = U1ReciMessage.ReciBuf[0];
		packetType = MQTT_HEADER_GET_TYPE(header.byte);
		
    switch (packetType) {
        case CONNACK: {
            break;
        }

        case PUBACK: {
            break;
        }

        case SUBACK: {
						rc = MQTTDeserialize_suback(&mypacketid, MUTLI_SUBSCIRBE_MAX, &count, grantedQoS, (unsigned char *)U1ReciMessage.ReciBuf,reciLen);
            break;
        }
				
        case PUBLISH: {
            recv_PUBLISH(reciLen);
            break;
        }
		
        case UNSUBACK: {

            break;
        }
        case PINGRESP: {

            break;
        }
        default:
            break;
    }
	}
}

