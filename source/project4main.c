

/*  SDK Included Files */
#include <delay.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "Driver_I2C.h"
#include "fsl_i2c_cmsis.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "slider.h"
#include "state.h"
#include"i2c.h"
#include "led.h"
#include "logger.h"

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_InitDebugConsole();



    KL25Z_RGB_Flasher();

    doCurrentState0();
}
