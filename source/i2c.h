#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "Driver_I2C.h"
#include "fsl_i2c_cmsis.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

//#include "stdb"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* I2C source clock */
#define EXAMPLE_I2C_MASTER Driver_I2C0

#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 25U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 24U
#define I2C_RELEASE_BUS_COUNT 100U
#define FXOS8700_WHOAMI 0xC7U
#define MMA8451_WHOAMI 0x1AU
#define ACCEL_STATUS 0x00U
#define ACCEL_XYZ_DATA_CFG 0x0EU
#define ACCEL_CTRL_REG1 0x2AU
/* FXOS8700 and MMA8451 have the same who_am_i register address. */
#define ACCEL_WHOAMI_REG 0x0DU
#define ACCEL_READ_TIMES 10U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void i2c_release_bus_delay(void);
void BOARD_I2C_ReleaseBus(void);
uint32_t I2C0_GetFreq(void);
void I2C_MasterSignalEvent_t(uint32_t event);

bool I2C_ReadAccelWhoAmI(void);
bool I2C_WriteAccelReg(uint8_t device_addr, uint8_t reg_addr, uint8_t value);
bool I2C_ReadAccelRegs(uint8_t device_addr, uint8_t reg_addr, uint8_t *rxBuff, uint32_t rxSize);

extern uint8_t g_accel_addr_found;
extern volatile bool completionFlag;
extern volatile bool nakFlag;

extern uint8_t databyte;
extern uint8_t write_reg;
extern uint8_t readBuff[7];
extern int16_t x, y, z;
extern uint8_t status0_value;
extern uint32_t i;
extern int32_t sumx,sumy,sumz;
extern int16_t maxx,maxy,maxz,minx,miny,minz;
