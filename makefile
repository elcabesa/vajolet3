################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here

C_UPPER_SRCS := 
CXX_SRCS := 
C++_SRCS := 
OBJ_SRCS := 
CC_SRCS := 
ASM_SRCS := 
CPP_SRCS := \
./benchmark.cpp \
./bitops.cpp \
./book.cpp \
./command.cpp \
./data.cpp \
./eval.cpp \
./hashKeys.cpp \
./io.cpp \
./magicmoves.cpp \
./movegen.cpp \
./position.cpp \
./search.cpp \
./see.cpp \
./thread.cpp \
./transposition.cpp \
./vajolet.cpp \
./syzygy/tbprobe.cpp 

C_SRCS := 
S_UPPER_SRCS := 
O_SRCS := 
CC_DEPS := 
C++_DEPS := 
EXECUTABLES := 
OBJS :=  \
./benchmark.o \
./bitops.o \
./book.o \
./command.o \
./data.o \
./eval.o \
./hashKeys.o \
./io.o \
./magicmoves.o \
./movegen.o \
./position.o \
./search.o \
./see.o \
./thread.o \
./transposition.o \
./vajolet.o \
./syzygy/tbprobe.o 
C_UPPER_DEPS := 
CXX_DEPS := 
CPP_DEPS := \
./benchmark.d \
./bitops.d \
./book.d \
./command.d \
./data.d \
./eval.d \
./hashKeys.d \
./io.d \
./magicmoves.d \
./movegen.d \
./position.d \
./search.d \
./see.d \
./thread.d \
./transposition.d \
./vajolet.d \
./syzygy/tbprobe.d 
C_DEPS := 

# Each subdirectory must supply rules for building sources it contributes
%.o: ./%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O3 -msse4.2 -mpopcnt -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
syzygy \

USER_OBJS :=

LIBS :=



ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: vajolet2.exe

# Tool invocations
vajolet2.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++ -s -static -pthread -o "vajolet2.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) vajolet2.exe
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
