################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TIMER.c \
../eeprom.c \
../i2c.c \
../main.c \
../motor.c \
../pwm.c \
../uart.c 

OBJS += \
./TIMER.o \
./eeprom.o \
./i2c.o \
./main.o \
./motor.o \
./pwm.o \
./uart.o 

C_DEPS += \
./TIMER.d \
./eeprom.d \
./i2c.d \
./main.d \
./motor.d \
./pwm.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


