#include "delay.h"
#include "state.h"



uint8_t to_start = 0;

state cur_state = start;

uint8_t n;


void Init_SysTick(void){
	n = 10;
	SysTick->LOAD = (48000000L/16);                //SysTick Reload Value Register (RVR) (RW) being run at 48MHz
	NVIC_SetPriority(SysTick_IRQn,3);
	SysTick->VAL = 0;                                                   //SysTick Current Value Register (CVR)
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; //Control and Status Register
}

void SysTick_Handler(){

	if(n == 0)
	{
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
		if(statemachine == 1)
		{
			cur_state = start;
		}
		else if(statemachine == 2)
		{
	    	timeoutcount--;
	    	if(timeoutcount == 0)
	    	{
	    		statemachine = 1;
	    		cur_state =start;
	    		timeoutcount = 5;
	    		doCurrentState0();
	    	}
			doCurrentState(&stateTable[0]);
		}
	}
	n--;
}





void delay(int num_ms)
{

	int delay_lookup[] = {240000,4800000,9600000,14000000}; //lookup table
	//------------------------------------------------------------------------------
	int keepgoing;
	//(ms*cpufreq_Mhz*1000)/10.. CPUfreq = 48MHz
	//int i = 0;
	int loopcount = 0;
	keepgoing = 1;

	if (num_ms == 50 )
	{
		loopcount = delay_lookup[0]; //count for 50ms
	}
	else if(num_ms == 1000)
	{
		loopcount = delay_lookup[1]; //count for 1000ms
	}
	else if(num_ms == 2000)
	{
		loopcount = delay_lookup[2]; //count for 2000ms
	}
	else if(num_ms == 3000)
	{
		loopcount = delay_lookup[3]; //count for 3000ms
	}

	while(keepgoing)  //always true
	{
		loopcount--;  //decrement duration
		if(loopcount <= 0) //time reached
			keepgoing = 0;   //exit delay
	}
}
