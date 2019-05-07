import RPi.GPIO as GPIO
import time

class Car(object):
    def __init__(self,motorPin,steerPin):
        self.motorPin = motorPin
        self.steerPin = steerPin

        GPIO.setmode(GPIO.BCM)
        GPIO.setup([motorPin,steerPin],GPIO.OUT)
        self.servo = GPIO.PWM(steerPin, 3000)
        self.motor = GPIO.PWM(motorPin, 3000)
        print("Car init")

    def reset(self):
        self.servo.start(0)
        self.motor.start(0)
        print("Car reset")

    def start(self):
        self.motor.start(0.51)
        self.servo.start(0.5)
        print("Car start")

    def stop(self):
        self.motor.ChangeDutyCycle(0.4)
        self.servo.ChangeDutyCycle(0.5)
        print("Car break")
        time.sleep(1)
        self.motor.ChangeDutyCycle(0)
        print("Break release")

    def steer(self,amount):
        amount = (max(-1,min(1,amount)) + 1) / 2
        self.servo.ChangeDutyCycle(amount)
        print("Car steer: ",amount)