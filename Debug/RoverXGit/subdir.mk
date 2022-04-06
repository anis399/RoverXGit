################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RoverXGit/ADXL345.c \
../RoverXGit/BMP180.c \
../RoverXGit/main.c \
../RoverXGit/nRF24L01+.c 

OBJS += \
./RoverXGit/ADXL345.o \
./RoverXGit/BMP180.o \
./RoverXGit/main.o \
./RoverXGit/nRF24L01+.o 

C_DEPS += \
./RoverXGit/ADXL345.d \
./RoverXGit/BMP180.d \
./RoverXGit/main.d \
./RoverXGit/nRF24L01+.d 


# Each subdirectory must supply rules for building sources it contributes
RoverXGit/%.o: ../RoverXGit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1404_Q064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

