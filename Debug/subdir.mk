################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../BackLogger.cc \
../ComputeMathMT2.cc \
../ComputeMathWithMultithread.cc \
../DoubleLock.cc \
../FlagSweepGCSimulator.cc \
../MtHashTableWithLog.cc \
../MtHashTableWithLog_Test.cc \
../Person.cc \
../Random.cc \
../SimpleBackTimer.cc \
../SimpleThreadPool.cc \
../TestLock_Guard.cc \
../Test_Atomic.cc \
../Test_CondionalValuable.cc \
../Test_Thread.cc \
../Test_Thread_Mutex.cc \
../Test_Time_Mutex.cc \
../ThreadExecuteWithSequence.cc \
../ThreadPoolBackTimer.cc \
../Utility.cc 

OBJS += \
./BackLogger.o \
./ComputeMathMT2.o \
./ComputeMathWithMultithread.o \
./DoubleLock.o \
./FlagSweepGCSimulator.o \
./MtHashTableWithLog.o \
./MtHashTableWithLog_Test.o \
./Person.o \
./Random.o \
./SimpleBackTimer.o \
./SimpleThreadPool.o \
./TestLock_Guard.o \
./Test_Atomic.o \
./Test_CondionalValuable.o \
./Test_Thread.o \
./Test_Thread_Mutex.o \
./Test_Time_Mutex.o \
./ThreadExecuteWithSequence.o \
./ThreadPoolBackTimer.o \
./Utility.o 

CC_DEPS += \
./BackLogger.d \
./ComputeMathMT2.d \
./ComputeMathWithMultithread.d \
./DoubleLock.d \
./FlagSweepGCSimulator.d \
./MtHashTableWithLog.d \
./MtHashTableWithLog_Test.d \
./Person.d \
./Random.d \
./SimpleBackTimer.d \
./SimpleThreadPool.d \
./TestLock_Guard.d \
./Test_Atomic.d \
./Test_CondionalValuable.d \
./Test_Thread.d \
./Test_Thread_Mutex.d \
./Test_Time_Mutex.d \
./ThreadExecuteWithSequence.d \
./ThreadPoolBackTimer.d \
./Utility.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/local/boost -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -Wl,--no-as-needed -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


