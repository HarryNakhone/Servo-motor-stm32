# Servomotor on Zephyr RTOS

Here is how you can run a servo motor using Zephyr RTOS
# Notes... you need to create a dts/bindings/ folder with the pwm-servo.yaml inside of it.
## If you skipped this step it won't be able to recognize the "compatible" property
## Required Tools 

STM32F4 Discovery
I am using S51 but you can use the different ones
A power supply, I used 5v
Jumper wires


### Prerequisites
- List (Zephyr, Python, VsCode etc...). Visit the website for more info

### Installation
```bash
# Example of running commands

#build 
west build -p always -b stm32f4_disco

#flash 

west flash
