################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AF.cpp \
../src/Argument.cpp \
../src/Boundcond.cpp \
../src/ExtendedArgument.cpp \
../src/Grounded.cpp \
../src/Labelling.cpp \
../src/OrClause.cpp \
../src/PrefAlgorithm.cpp \
../src/Preferred.cpp \
../src/SATFormulae.cpp \
../src/SCCSEQ.cpp \
../src/SetArguments.cpp \
../src/SetArgumentsVector.cpp \
../src/main.cpp \
../src/misc.cpp 

OBJS += \
./src/AF.o \
./src/Argument.o \
./src/Boundcond.o \
./src/ExtendedArgument.o \
./src/Grounded.o \
./src/Labelling.o \
./src/OrClause.o \
./src/PrefAlgorithm.o \
./src/Preferred.o \
./src/SATFormulae.o \
./src/SCCSEQ.o \
./src/SetArguments.o \
./src/SetArgumentsVector.o \
./src/main.o \
./src/misc.o 

CPP_DEPS += \
./src/AF.d \
./src/Argument.d \
./src/Boundcond.d \
./src/ExtendedArgument.d \
./src/Grounded.d \
./src/Labelling.d \
./src/OrClause.d \
./src/PrefAlgorithm.d \
./src/Preferred.d \
./src/SATFormulae.d \
./src/SCCSEQ.d \
./src/SetArguments.d \
./src/SetArgumentsVector.d \
./src/main.d \
./src/misc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DNLOGPRECO -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


