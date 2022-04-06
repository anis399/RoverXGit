################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RoverX/Libraries/XMCLib/src/xmc1_eru.c \
../RoverX/Libraries/XMCLib/src/xmc1_flash.c \
../RoverX/Libraries/XMCLib/src/xmc1_gpio.c \
../RoverX/Libraries/XMCLib/src/xmc1_rtc.c \
../RoverX/Libraries/XMCLib/src/xmc1_scu.c \
../RoverX/Libraries/XMCLib/src/xmc_acmp.c \
../RoverX/Libraries/XMCLib/src/xmc_bccu.c \
../RoverX/Libraries/XMCLib/src/xmc_can.c \
../RoverX/Libraries/XMCLib/src/xmc_ccu4.c \
../RoverX/Libraries/XMCLib/src/xmc_ccu8.c \
../RoverX/Libraries/XMCLib/src/xmc_common.c \
../RoverX/Libraries/XMCLib/src/xmc_eru.c \
../RoverX/Libraries/XMCLib/src/xmc_gpio.c \
../RoverX/Libraries/XMCLib/src/xmc_i2c.c \
../RoverX/Libraries/XMCLib/src/xmc_i2s.c \
../RoverX/Libraries/XMCLib/src/xmc_ledts.c \
../RoverX/Libraries/XMCLib/src/xmc_math.c \
../RoverX/Libraries/XMCLib/src/xmc_pau.c \
../RoverX/Libraries/XMCLib/src/xmc_posif.c \
../RoverX/Libraries/XMCLib/src/xmc_prng.c \
../RoverX/Libraries/XMCLib/src/xmc_rtc.c \
../RoverX/Libraries/XMCLib/src/xmc_spi.c \
../RoverX/Libraries/XMCLib/src/xmc_uart.c \
../RoverX/Libraries/XMCLib/src/xmc_usic.c \
../RoverX/Libraries/XMCLib/src/xmc_vadc.c \
../RoverX/Libraries/XMCLib/src/xmc_wdt.c 

OBJS += \
./RoverX/Libraries/XMCLib/src/xmc1_eru.o \
./RoverX/Libraries/XMCLib/src/xmc1_flash.o \
./RoverX/Libraries/XMCLib/src/xmc1_gpio.o \
./RoverX/Libraries/XMCLib/src/xmc1_rtc.o \
./RoverX/Libraries/XMCLib/src/xmc1_scu.o \
./RoverX/Libraries/XMCLib/src/xmc_acmp.o \
./RoverX/Libraries/XMCLib/src/xmc_bccu.o \
./RoverX/Libraries/XMCLib/src/xmc_can.o \
./RoverX/Libraries/XMCLib/src/xmc_ccu4.o \
./RoverX/Libraries/XMCLib/src/xmc_ccu8.o \
./RoverX/Libraries/XMCLib/src/xmc_common.o \
./RoverX/Libraries/XMCLib/src/xmc_eru.o \
./RoverX/Libraries/XMCLib/src/xmc_gpio.o \
./RoverX/Libraries/XMCLib/src/xmc_i2c.o \
./RoverX/Libraries/XMCLib/src/xmc_i2s.o \
./RoverX/Libraries/XMCLib/src/xmc_ledts.o \
./RoverX/Libraries/XMCLib/src/xmc_math.o \
./RoverX/Libraries/XMCLib/src/xmc_pau.o \
./RoverX/Libraries/XMCLib/src/xmc_posif.o \
./RoverX/Libraries/XMCLib/src/xmc_prng.o \
./RoverX/Libraries/XMCLib/src/xmc_rtc.o \
./RoverX/Libraries/XMCLib/src/xmc_spi.o \
./RoverX/Libraries/XMCLib/src/xmc_uart.o \
./RoverX/Libraries/XMCLib/src/xmc_usic.o \
./RoverX/Libraries/XMCLib/src/xmc_vadc.o \
./RoverX/Libraries/XMCLib/src/xmc_wdt.o 

C_DEPS += \
./RoverX/Libraries/XMCLib/src/xmc1_eru.d \
./RoverX/Libraries/XMCLib/src/xmc1_flash.d \
./RoverX/Libraries/XMCLib/src/xmc1_gpio.d \
./RoverX/Libraries/XMCLib/src/xmc1_rtc.d \
./RoverX/Libraries/XMCLib/src/xmc1_scu.d \
./RoverX/Libraries/XMCLib/src/xmc_acmp.d \
./RoverX/Libraries/XMCLib/src/xmc_bccu.d \
./RoverX/Libraries/XMCLib/src/xmc_can.d \
./RoverX/Libraries/XMCLib/src/xmc_ccu4.d \
./RoverX/Libraries/XMCLib/src/xmc_ccu8.d \
./RoverX/Libraries/XMCLib/src/xmc_common.d \
./RoverX/Libraries/XMCLib/src/xmc_eru.d \
./RoverX/Libraries/XMCLib/src/xmc_gpio.d \
./RoverX/Libraries/XMCLib/src/xmc_i2c.d \
./RoverX/Libraries/XMCLib/src/xmc_i2s.d \
./RoverX/Libraries/XMCLib/src/xmc_ledts.d \
./RoverX/Libraries/XMCLib/src/xmc_math.d \
./RoverX/Libraries/XMCLib/src/xmc_pau.d \
./RoverX/Libraries/XMCLib/src/xmc_posif.d \
./RoverX/Libraries/XMCLib/src/xmc_prng.d \
./RoverX/Libraries/XMCLib/src/xmc_rtc.d \
./RoverX/Libraries/XMCLib/src/xmc_spi.d \
./RoverX/Libraries/XMCLib/src/xmc_uart.d \
./RoverX/Libraries/XMCLib/src/xmc_usic.d \
./RoverX/Libraries/XMCLib/src/xmc_vadc.d \
./RoverX/Libraries/XMCLib/src/xmc_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
RoverX/Libraries/XMCLib/src/%.o: ../RoverX/Libraries/XMCLib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1404_Q064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

