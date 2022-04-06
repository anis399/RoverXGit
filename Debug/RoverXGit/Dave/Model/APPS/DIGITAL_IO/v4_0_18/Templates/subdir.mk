################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RoverXGit/Dave/Model/APPS/DIGITAL_IO/v4_0_18/Templates/digital_io.c 

OBJS += \
./RoverXGit/Dave/Model/APPS/DIGITAL_IO/v4_0_18/Templates/digital_io.o 

C_DEPS += \
./RoverXGit/Dave/Model/APPS/DIGITAL_IO/v4_0_18/Templates/digital_io.d 


# Each subdirectory must supply rules for building sources it contributes
RoverXGit/Dave/Model/APPS/DIGITAL_IO/v4_0_18/Templates/%.o: ../RoverXGit/Dave/Model/APPS/DIGITAL_IO/v4_0_18/Templates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1404_Q064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

