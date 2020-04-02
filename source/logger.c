#include "stdlib.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"


uint8_t status;



void Log_statusenable()
{
	 status = 1;
}

void Log_statusdisable()
{
	 status = 0;
}

 void Log_data(uint32_t* ptr)
 {
 	if (status == 1)
 	{
 		PRINTF("Memory allocated at 0x%08X Hex is %x ",(ptr),*(ptr));
 	}

 }

void Log_string(char* s)
{	if(status ==1)
	{
		PRINTF("%s ",s);
	}
}

void Log_integer_format(int d)
{	if(status ==1)
	{
		PRINTF("%08d ",d);
	}
}

void Log_function(level l,functionname n)
{
	if(l == Test)
	{
		if(n == isthereAccel)
		{
			printf("Test: Post Testing Done\n");
		}
		else if(n == I2C_writeAccelReg)
		{
			printf("Test: Configure The Accelerometer\n");
		}
		else if(n == I2C_readAccelRegs)
		{
			printf("Test: Reading The Accelerometer\n");
		}
		else if(n == Touch_scan_LH)
		{
			printf("Test: Polling the Touch Sensor\n");
		}
		else if(n == LED)
		{
			printf("Test: The LED is On");
		}
		else
		{
			printf("Test: No Such Function\n");
		}
	}
	else if(l == Debug)
	{
		if(n == isthereAccel)
		{
			printf("Debug: Post Testing Done\n");
		}
		else if(n == I2C_writeAccelReg)
		{
			printf("Debug: Configure The Accelerometer\n");
		}
		else if(n == I2C_readAccelRegs)
		{
			printf("Debug: Reading The Accelerometer\n");
		}
		else if(n == Touch_scan_LH)
		{
			printf("Debug: Polling the Touch Sensor\n");
		}
		else if(n == LED)
		{
			printf("Test: The LED is On");
		}
		else
		{
			printf("Debug: No Such Function\n");
		}
	}
	else if(l == Status)
	{
		if(n == isthereAccel)
		{
			printf("Status: Post Testing Done\n");
		}
		else if(n == Touch_scan_LH)
		{
			printf("Status: Polling the Touch Sensor\n");
		}
		else if(n == LED)
		{
			printf("Test: The LED is On");
		}
		else
		{
			printf("Status: No Such Function\n");
		}
	}

}
