#include "Car.h"
#include <pigpio.h>
#include <iostream>

Car::Car(int motorPin, int servoPin)
{
    if (gpioInitialise() < 0)
    {
        std::cout << "Init failed" << std::endl;
        exit(0);
    }
    gpioSetMode(motorPin, PI_OUTPUT);
    gpioSetMode(servoPin, PI_OUTPUT);
    ServoPin = servoPin;
    MotorPin = motorPin;
}

Car::~Car()
{
    gpioTerminate();
}

void Car::start()
{
    gpioServo(ServoPin,1500);
    time_sleep(0.1);
    gpioServo(MotorPin,1530);
    time_sleep(0.1);
}

void Car::stop()
{
    gpioServo(ServoPin,0);
    time_sleep(0.1);
    gpioServo(MotorPin,0);
    time_sleep(0.1);

}

void Car::reset()
{
    gpioServo(ServoPin,0);
    time_sleep(0.1);
    gpioServo(MotorPin,0);
    time_sleep(0.1);

}

void Car::steer(double amount)
{
    int pwm = 1500 + std::min(1.0,std::max(-1.0,amount)) * 100;
    gpioServo(ServoPin,pwm);
    time_sleep(0.1);

}
