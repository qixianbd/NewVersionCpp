################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../DoubleLock.cc \
../Logger.cc \
../Test_Atomic.cc \
../Test_Thread.cc \
../Test_Thread_Mutex.cc \
../main.cc 

OBJS += \
./DoubleLock.o \
./Logger.o \
./Test_Atomic.o \
./Test_Thread.o \
./Test_Thread_Mutex.o \
./main.o 

CC_DEPS += \
./DoubleLock.d \
./Logger.d \
./Test_Atomic.d \
./Test_Thread.d \
./Test_Thread_Mutex.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


