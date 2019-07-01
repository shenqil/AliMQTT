#ifndef __IOTX_MQTT_H__
#define __IOTX_MQTT_H__


typedef enum {
    IOTX_MC_CONNECTION_ACCEPTED = 0,
    IOTX_MC_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION = 1,
    IOTX_MC_CONNECTION_REFUSED_IDENTIFIER_REJECTED = 2,
    IOTX_MC_CONNECTION_REFUSED_SERVER_UNAVAILABLE = 3,
    IOTX_MC_CONNECTION_REFUSED_BAD_USERDATA = 4,
    IOTX_MC_CONNECTION_REFUSED_NOT_AUTHORIZED = 5
} iotx_mc_connect_ack_code_t;




int AliMQTTConnect(void);
void subscribeExample(void);
void publishExample(void);
void Ali_MQTT_Yield(void);

#endif



