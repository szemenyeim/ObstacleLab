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
        self.motor.start(7.65)
        self.servo.start(7.5)
        print("Car start")

    def stop(self):
        self.motor.ChangeDutyCycle(6.5)
        self.servo.ChangeDutyCycle(7.5)
        print("Car break")
        time.sleep(1)
        self.motor.ChangeDutyCycle(0)
        self.servo.ChangeDutyCycle(0)
        print("Break release")

    def steer(self,amount):
        amount = 7.5 + (max(-1,min(1,amount)))
        self.servo.ChangeDutyCycle(amount)
        print("Car steer: ",amount)