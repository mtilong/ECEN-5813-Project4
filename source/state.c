#include "state.h"
#include "i2c.h"
#include "delay.h"
#include "slider.h"
#include "led.h"
#include "logger.h"
#include "math.h"

uint8_t statemachine = 1;

uint8_t timeoutcount = 5;

bool isThereAccel = false;




 struct sStateTableEntry stateTable[]= {
		{readxyz,processdisplay,sensordisconnect,end},
		{processdisplay,waitslider,end,end},
		{waitslider,end,end,readxyz},
		{sensordisconnect,end,end,end}
};

void doCurrentState0()
{

	 while (1)
	    {
	        switch (cur_state)
	        {
	            case start:
	            	printf("Now in state machine 1\n");
	                isThereAccel = I2C_ReadAccelWhoAmI();
	                Log_function(Test,isthereAccel);
	                cur_state = testing_complete;
	                break;

	            case testing_complete:
	                write_reg = ACCEL_CTRL_REG1;
	                databyte = 0;
	                I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
	                write_reg = ACCEL_XYZ_DATA_CFG;
	                databyte = 0x01;
	                I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
	                write_reg = ACCEL_CTRL_REG1;
	                databyte = 0x0d;
	                I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
	                Log_function(Test,I2C_writeAccelReg);
	                cur_state = read_complete;

	                LED_cycleblue_On(); //turn on blue LED
	                delay(1000);
	                LED_off();
	                break;

	            case read_complete:
	            	LED_cyclegreen_On();
	            	delay(50000);
	            	LED_off();
	                PRINTF("The accel values:\r\n");
	                for (i = 0; i < ACCEL_READ_TIMES; i++)
	                {
	                    status0_value = 0;

	                    /*  wait for new data are ready. */
	                    while (status0_value != 0xff)
	                    {
	                        I2C_ReadAccelRegs(g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
	                    }

	                    /*  Multiple-byte Read from STATUS (0x00) register */
	                    I2C_ReadAccelRegs(g_accel_addr_found, ACCEL_STATUS, readBuff, 7);
	                    Log_function(Test,I2C_readAccelRegs);
	                    status0_value = readBuff[0];
	                    x = ((int16_t)(((readBuff[1] * 256U) | readBuff[2]))) / 4U;
	                    y = ((int16_t)(((readBuff[3] * 256U) | readBuff[4]))) / 4U;
	                    z = ((int16_t)(((readBuff[5] * 256U) | readBuff[6]))) / 4U;

	                    PRINTF("status_reg = 0x%x , x = %5d , y = %5d , z = %5d \r\n", status0_value, x, y, z);
	                }
	                cur_state = display_complete;
	                break;

	            case display_complete:
	            	LED_cyclegreen_On();
	            	delay(1000);
	            	LED_off();
	            	Init_SysTick();
	            	Touch_Init();
	            	Log_function(Test,Touch_scan_LH);
	            	while(cur_state==display_complete){

	            		  uint32_t x = Touch_Scan_LH();
	            		  delay(50);

	            		  x = Touch_Scan_LH();
	                  	  SysTick_Handler();
	            		  //printf("Touch Value: %u\n", x);
	            		  if(x > 400)
	            		  {
	            		    cur_state = end;
	            			SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	            		    break;
	            		   }
	            	}
	            	timeoutcount--;
	            	if(timeoutcount == 0)
	            	{
	            		statemachine = 2;
	            		timeoutcount = 5;
	            		doCurrentState(&stateTable[0]);
	            	}
	    			break;

	            case end:
	            	LED_cyclered_On(); //turn on red LED
	            	Log_function(Test,LED);
	            	break;
	            default:
	            	break;
	        }
	    }
}


void doCurrentState(struct sStateTableEntry* currentState)
{
	if(currentState->current == readxyz)
	{
		LED_cyclegreen_On();
		delay(1000);
		LED_off();
		printf("Now in state machine 2\n");
        write_reg = ACCEL_CTRL_REG1;
        databyte = 0;
        I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
        write_reg = ACCEL_XYZ_DATA_CFG;
        databyte = 0x01;
        I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
        write_reg = ACCEL_CTRL_REG1;
        databyte = 0x0d;
        I2C_WriteAccelReg(g_accel_addr_found, write_reg, databyte);
        for (i = 0; i < ACCEL_READ_TIMES; i++)
        {
            status0_value = 0;
            /*  wait for new data are ready. */
            while (status0_value != 0xff)
            {
                I2C_ReadAccelRegs(g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
            }
            /*  Multiple-byte Read from STATUS (0x00) register */
            I2C_ReadAccelRegs(g_accel_addr_found, ACCEL_STATUS, readBuff, 7);
        }
        doCurrentState(&stateTable[1]);
	}

	else if(currentState->current == processdisplay)
	{
		LED_cyclegreen_On();
		delay(1000);
		LED_off();

        for (i = 0; i < ACCEL_READ_TIMES; i++)
        {

            /*  Multiple-byte Read from STATUS (0x00) register */
            I2C_ReadAccelRegs(g_accel_addr_found, ACCEL_STATUS, readBuff, 7);

            status0_value = readBuff[0];
            x = ((int16_t)(((readBuff[1] * 256U) | readBuff[2]))) / 4U;
            y = ((int16_t)(((readBuff[3] * 256U) | readBuff[4]))) / 4U;
            z = ((int16_t)(((readBuff[5] * 256U) | readBuff[6]))) / 4U;
            sumx += x;
            sumy += y;
            sumz += z;
            if(i == 0)
            {
            	minx = x;
            	miny = y;
            	minz = z;
            }
            if( x > maxx)
            {
            	maxx = x;
            }
            if( y > maxy)
            {
            	maxy = y;
            }
            if (z > maxz)
            {
            	maxz = z;
            }
            if( x < minx)
            {
            	minx = x;
            }
            if( y < miny)
            {
            	miny = y;
            }
            if( z < minz)
            {
            	minz = z;
            }
            PRINTF("status_reg = 0x%x , x = %5d , y = %5d , z = %5d \r\n", status0_value, x, y, z);
            if(i == ACCEL_READ_TIMES-1)
            {
            	PRINTF("status_reg = 0x%x ,the last value: x = %5d , y = %5d , z = %5d \r\n", status0_value, x, y, z);
            	PRINTF("status_reg = 0x%x ,the average value: x = %5d , y = %5d , z = %5d \r\n", status0_value,
            			sumx/ACCEL_READ_TIMES, sumy/ACCEL_READ_TIMES, sumz/ACCEL_READ_TIMES);
            	PRINTF("status_reg = 0x%x ,the maximum value: x = %5d , y = %5d , z = %5d \r\n", status0_value, maxx, maxy, maxz);
            	PRINTF("status_reg = 0x%x ,the minimum value: x = %5d , y = %5d , z = %5d \r\n", status0_value, minx, miny, minz);
            }
        }
        doCurrentState(&stateTable[2]);
	}

	else if(currentState->current == waitslider)
	{
		LED_cyclegreen_On();
		delay(1000);
		LED_off();

		Init_SysTick();
    	Touch_Init();
    	while(currentState->current == waitslider){

    		  uint32_t x = Touch_Scan_LH();
    		  delay(50);

    		  x = Touch_Scan_LH();
          	  SysTick_Handler();
    		  //printf("Touch Value: %u\n", x);
    		  if(x > 400)
    		  {
    			SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    		    doCurrentState(&stateTable[3]);
    		  }
    	}

	}

	else if(currentState->current == sensordisconnect)
	{
		while(1){
			LED_cyclered_On(); //turn on red LED
		}
	}
}

