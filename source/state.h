#include "stdint.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "Driver_I2C.h"
#include "fsl_i2c_cmsis.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

extern uint8_t timeoutcount;

extern uint8_t to_start;

typedef enum state {
		start,
		testing_complete,
		read_complete,
		display_complete,
		end
}state;

//state2 states
typedef enum STATE {
	readxyz,
	processdisplay,
	waitslider,
	sensordisconnect,
}STATE;

struct sStateTableEntry
{
	STATE current;
	STATE complete;
	STATE disconnected;
	STATE timeout;
};


void doCurrentState(struct sStateTableEntry* currentState);

void doCurrentState0();

extern state cur_state;

extern uint8_t statemachine;

extern struct sStateTableEntry stateTable[];

extern bool isThereAccel;
