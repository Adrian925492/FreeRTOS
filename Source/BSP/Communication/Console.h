#include <stdint.h>

void Console_Init();

void consoleSend(unsigned char* pData);
void consoleSendByte(unsigned char* data);

void consoleRead(unsigned char* pData, uint16_t length, uint16_t timeout);
