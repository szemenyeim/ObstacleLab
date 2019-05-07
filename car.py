import RPi.GPIO as GPIO
import time

class Car(object):
    def __init__(self,motorPin,steerPin):
        self.motorPin = motorPin
        self.steerPin = steerPin

        GPIO.setmode(GPIO.BCM)
        GPIO.setup([motorPin,steerPin],GPIO.OUT)
        self.servo = GPIO.PWM(steerPin, 50)
        self.motor = GPIO.PWM(motorPin, 50)
        print("Car init")

    def reset(self):
        self.servo.start(0)
        self.motor.start(0)
        print("Car reset")

    def start(self):
        self.motor.start(5.05)
        self.servo.start(5.0)
        print("Car start")

    def stop(self):
        self.motor.ChangeDutyCycle(4.0)
        self.servo.ChangeDutyCycle(5.0)
        print("Car break")
        time.sleep(1)
        self.motor.ChangeDutyCycle(0)
        print("Break release")

    def steer(self,amount):
        amount = 5 + (max(-1,min(1,amount)) + 1) * 2.5
        self.servo.ChangeDutyCycle(amount)
        print("Car steer: ",amount)