#pragma once

class Car
{
protected:
    int ServoPin;
    int MotorPin;
public:
	Car(int motorPin, int ServoPin);
    ~Car();
	void start();
	void stop();
	void reset();
	void steer(double amount);
};
