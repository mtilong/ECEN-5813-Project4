typedef enum functionname
{
	isthereAccel,
	I2C_writeAccelReg,
	I2C_readAccelRegs,
	Touch_scan_LH,
	LED,
}functionname;

typedef enum level
{
	Test,
	Debug,
	Status,
}level;

 void Log_enable();

 void Log_disable();

uint8_t Log_status();

void Log_data(uint32_t* ptr);

void Log_string(char* s);

void Log_integer_format(int d);

void Log_function(level l,functionname n);

void Log_level(level n);


