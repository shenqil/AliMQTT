/**
 * NOTE:
 *
 * HAL_TCP_xxx API reference implementation: wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 */
#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "wrappers_defs.h"
#include "stdarg.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stm32f1xx_hal.h"
#include "usart.h"

#define EXAMPLE_PRODUCT_KEY         "a1zPE6uuzgg"
#define EXAMPLE_PRODUCT_SECRET      "QRmgUqI54PQqZLLyL9N8LcJz1DCIBLHQ"
#define EXAMPLE_DEVICE_NAME         "device"
#define EXAMPLE_DEVICE_SECRET       "QRmgUqI54PQqZLLyL9N8LcJz1DCIBLHQ"

#define EXAMPLE_FIRMWARE_VERSION    "app-1.0.0-20190118.1000"

/**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Free(void *ptr)
{
	free(ptr);
	return;
}


/**
 * @brief Get device name from user's system persistent storage
 *
 * @param [ou] device_name: array to store device name, max length is IOTX_DEVICE_NAME_LEN
 * @return the actual length of device name
 */
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1])
{
	int len = strlen(EXAMPLE_DEVICE_NAME);
	if(len >= IOTX_DEVICE_NAME_LEN){
			return -1;
	}
	memset(device_name, 0x0, IOTX_DEVICE_NAME_LEN); 
	strncpy(device_name, EXAMPLE_DEVICE_NAME, len); 
	return strlen(device_name);
}


/**
 * @brief Get device secret from user's system persistent storage
 *
 * @param [ou] device_secret: array to store device secret, max length is IOTX_DEVICE_SECRET_LEN
 * @return the actual length of device secret
 */
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN + 1])
{
	int len = strlen(EXAMPLE_DEVICE_SECRET); 
	if(len >= IOTX_DEVICE_SECRET_LEN){
			return -1;
	}
	
	memset(device_secret, 0x0, IOTX_DEVICE_SECRET_LEN); 
	strncpy(device_secret, EXAMPLE_DEVICE_SECRET, len); 
	return len;
}


/**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
int HAL_GetFirmwareVersion(char *version)
{
	int len = strlen(EXAMPLE_FIRMWARE_VERSION);
	if(len >= IOTX_FIRMWARE_VER_LEN-1){
			return -1;
	}
	memset(version, 0x0, IOTX_FIRMWARE_VER_LEN);
	strncpy(version, EXAMPLE_FIRMWARE_VERSION, len);
	version[len] = '\0';
	return strlen(version);
}


/**
 * @brief Get product key from user's system persistent storage
 *
 * @param [ou] product_key: array to store product key, max length is IOTX_PRODUCT_KEY_LEN
 * @return  the actual length of product key
 */
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1])
{
	int len = strlen(EXAMPLE_PRODUCT_KEY); 
	if(len >= IOTX_PRODUCT_KEY_LEN){
			return -1;
	}
	memset(product_key, 0x0, IOTX_PRODUCT_KEY_LEN); 
	strncpy(product_key, EXAMPLE_PRODUCT_KEY, len); 
	return len;
}


// EXAMPLE_PRODUCT_SECRET
int HAL_GetProductSecret(char product_secret[IOTX_PRODUCT_SECRET_LEN + 1])
{
	int len = strlen(EXAMPLE_PRODUCT_SECRET); 
	if(len >= IOTX_PRODUCT_SECRET_LEN){
			return -1;
	}
	memset(product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN); 
	strncpy(product_secret, EXAMPLE_PRODUCT_SECRET, len); 
	return len;
}


/**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
void *HAL_Malloc(uint32_t size)
{
	void* addr = malloc(size);
	return addr;
}


/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
	return (void*)1;
}


/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
	return;
}


/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
	return;
}


/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
	return;
}


/**
 * @brief Writes formatted data to stream.
 *
 * @param [in] fmt: @n String that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Printf(const char *fmt, ...)
{
	return;
}


uint32_t HAL_Random(uint32_t region)
{
	return (uint32_t)1;
}


/**
 * @brief Sleep thread itself.
 *
 * @param [in] ms @n the time interval for which execution is to be suspended, in milliseconds.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SleepMs(uint32_t ms)
{
	HAL_Delay(ms);
}


/**
 * @brief Writes formatted data to string.
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
	  va_list args; 
    int rc; 

    va_start(args, fmt); 
    rc = vsnprintf(str, len, fmt, args); 
    va_end(args); 
    return rc;
}


void HAL_Srandom(uint32_t seed)
{
	return;
}


/**
 * @brief Destroy the specific TCP connection.
 *
 * @param [in] fd: @n Specify the TCP connection by handle.
 *
 * @return The result of destroy TCP connection.
 * @retval < 0 : Fail.
 * @retval   0 : Success.
 */
int HAL_TCP_Destroy(uintptr_t fd)
{
	return (int)0;
}


/**
 * @brief Establish a TCP connection.
 *
 * @param [in] host: @n Specify the hostname(IP) of the TCP server
 * @param [in] port: @n Specify the TCP port of TCP server
 *
 * @return The handle of TCP connection.
   @retval (uintptr_t)(-1): Fail.
   @retval All other values(0 included): Success, the value is handle of this TCP connection.
 */
uintptr_t HAL_TCP_Establish(const char *host, uint16_t port)
{
	return (uintptr_t)1;
}


/**
 * @brief Read data from the specific TCP connection with timeout parameter.
 *        The API will return immediately if 'len' be received from the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a TCP connection.
 * @param [out] buf @n A pointer to a buffer to receive incoming data.
 * @param [out] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval       -2 : TCP connection error occur.
 * @retval       -1 : TCP connection be closed by remote server.
 * @retval        0 : No any data be received in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be received in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Read(uintptr_t fd, char *buf, uint32_t len, uint32_t timeout_ms)
{
	return MQTTgetData((uint8_t*)buf,len,timeout_ms);
}


/**
 * @brief Write data into the specific TCP connection.
 *        The API will return immediately if 'len' be written into the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a connection.
 * @param [in] buf @n A pointer to a buffer containing the data to be transmitted.
 * @param [in] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval      < 0 : TCP connection error occur..
 * @retval        0 : No any data be write into the TCP connection in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be written in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Write(uintptr_t fd, const char *buf, uint32_t len, uint32_t timeout_ms)
{
	UART_SendFrame((uint8_t*)buf,len);
	return len;
}


/**
 * @brief Retrieves the number of milliseconds that have elapsed since the system was boot.
 *
 * @return the number of milliseconds.
 * @see None.
 * @note None.
 */
uint64_t HAL_UptimeMs(void)
{
	return HAL_GetTick();
}


int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap)
{
	while(1);

	return (int)1;
}


