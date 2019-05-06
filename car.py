import pigpio as pi
import time

class Car(object):
    def __init__(self,motorPin,steerPin):
        self.motorPin = motorPin
        self.steerPin = steerPin
        pi.set_servo_pulsewidth(motorPin, 0)
        pi.set_servo_pulsewidth(steerPin, 0)

    def reset(self):
        pi.set_servo_pulsewidth(self.motorPin, 0)
        pi.set_servo_pulsewidth(self.steerPin, 0)

    def start(self):
        pi.set_servo_pulsewidth(self.motorPin, 1530)
        pi.set_servo_pulsewidth(self.steerPin, 1500)

    def stop(self):
        pi.set_servo_pulsewidth(self.motorPin, 1200)
        pi.set_servo_pulsewidth(self.steerPin, 1500)
        time.sleep(1)
        pi.set_servo_pulsewidth(self.motorPin, 0)

    def steer(self,amount):
        amount = 1500 + max(-1,min(1,amount)) * 250
        pi.set_servo_pulsewidth(self.steerPin, amount)