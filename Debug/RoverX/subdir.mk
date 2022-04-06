################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RoverX/ADXL345.c \
../RoverX/BMP180.c \
../RoverX/main.c \
../RoverX/nRF24L01+.c 

OBJS += \
./RoverX/ADXL345.o \
./RoverX/BMP180.o \
./RoverX/main.o \
./RoverX/nRF24L01+.o 

C_DEPS += \
./RoverX/ADXL345.d \
./RoverX/BMP180.d \
./RoverX/main.d \
./RoverX/nRF24L01+.d 


# Each subdirectory must supply rules for building sources it contributes
RoverX/%.o: ../RoverX/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1404_Q064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

