################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/precosat/precobnr.cc \
../src/precosat/precomain.cc \
../src/precosat/precosat.cc 

OBJS += \
./src/precosat/precobnr.o \
./src/precosat/precomain.o \
./src/precosat/precosat.o 

CC_DEPS += \
./src/precosat/precobnr.d \
./src/precosat/precomain.d \
./src/precosat/precosat.d 


# Each subdirectory must supply rules for building sources it contributes
src/precosat/%.o: ../src/precosat/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DNLOGPRECO -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


