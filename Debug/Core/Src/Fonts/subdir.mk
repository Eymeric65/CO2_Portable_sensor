################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Fonts/FontCO2.c \
../Core/Src/Fonts/FontINFO.c \
../Core/Src/Fonts/FontTIME.c 

OBJS += \
./Core/Src/Fonts/FontCO2.o \
./Core/Src/Fonts/FontINFO.o \
./Core/Src/Fonts/FontTIME.o 

C_DEPS += \
./Core/Src/Fonts/FontCO2.d \
./Core/Src/Fonts/FontINFO.d \
./Core/Src/Fonts/FontTIME.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Fonts/%.o Core/Src/Fonts/%.su Core/Src/Fonts/%.cyclo: ../Core/Src/Fonts/%.c Core/Src/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Fonts

clean-Core-2f-Src-2f-Fonts:
	-$(RM) ./Core/Src/Fonts/FontCO2.cyclo ./Core/Src/Fonts/FontCO2.d ./Core/Src/Fonts/FontCO2.o ./Core/Src/Fonts/FontCO2.su ./Core/Src/Fonts/FontINFO.cyclo ./Core/Src/Fonts/FontINFO.d ./Core/Src/Fonts/FontINFO.o ./Core/Src/Fonts/FontINFO.su ./Core/Src/Fonts/FontTIME.cyclo ./Core/Src/Fonts/FontTIME.d ./Core/Src/Fonts/FontTIME.o ./Core/Src/Fonts/FontTIME.su

.PHONY: clean-Core-2f-Src-2f-Fonts

