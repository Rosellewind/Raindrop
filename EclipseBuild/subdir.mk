################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Animation.cpp \
../Cup.cpp \
../Drop.cpp \
../Frame.cpp \
../Game.cpp \
../Menu.cpp \
../Pane.cpp \
../RaindropGame.cpp \
../SoundPlayer.cpp \
../Sprite.cpp \
../Text.cpp \
../Timer.cpp \
../main.cpp 

OBJS += \
./Animation.o \
./Cup.o \
./Drop.o \
./Frame.o \
./Game.o \
./Menu.o \
./Pane.o \
./RaindropGame.o \
./SoundPlayer.o \
./Sprite.o \
./Text.o \
./Timer.o \
./main.o 

CPP_DEPS += \
./Animation.d \
./Cup.d \
./Drop.d \
./Frame.d \
./Game.d \
./Menu.d \
./Pane.d \
./RaindropGame.d \
./SoundPlayer.d \
./Sprite.d \
./Text.d \
./Timer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Spike\git\Raindrop\Resources" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


