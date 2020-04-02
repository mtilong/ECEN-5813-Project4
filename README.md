# ECEN-5813-Project4
ECEN 5813 project 4

This repository includes an I2C driver to br able to communicte with the KL25Z onboard MMA8451 accelerometer. The software suit contaings two state machines. The first state machines is a classic switch based state machine and the second state machine is a table based state machine. There is a Logger function that outputs status, debug and test messages to UART.The code has been tested Using MCUXPresso on the FRDM-KL25Z dev board.

# Observations
The I2C code written was leveraged from an already existing SDK example. This SDK example has been the only I2C code we were able to make functional. We tried to follow the directionof the lecture and the example provided within the assignement but the code was not functional. As a result we leveraged what was functional.

# Builup
Pull the repo from github
Import it into MCUXpresso IDE
Simply run the function. Since it is the onboard accelerometer that is being used, no added hardware is need. 

# Repo Content in The Source File
delay.c
delay.h
i2c.c
i2c.h
led.c
led.h
logger.c
logger.h
slider.c
slider.h
state.c
state.h
project4main.c
