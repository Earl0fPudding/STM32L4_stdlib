// function prototypes
void initUsart1(uint32_t baud, uint64_t clockspeed);
void serialPrint(char* string);
void serialPrintLine(char* string);
void serialSendData(uint8_t data);
void serialSTX(void);
void serialETX(void);
void serialNewLine(void);
void serialSendBulkData(uint8_t* collection);
