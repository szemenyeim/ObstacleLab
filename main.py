from car import Car
from vision import Vision
from camera import Camera
import cv2
import numpy as np

if __name__ == '__main__':
    car = Car(18,12)
    vision = Vision(0.1)
    camera = Camera()

    #car.start()

    while True:
        _ ,depth = camera.getImages()
        if depth is None:
            #car.stop()
            #car.reset()
            break

        ret = vision.processFrame(depth)
        cv2.imshow("depth",depth/np.max(depth))
        key = cv2.waitKey(1)
        if key == 119:
            car.start()
        elif key == 115:
            car.stop()
        elif key == 97:
            car.steer(-1)
        elif key == 100:
            car.steer(1)
        if ret:
            car.stop()
            car.reset()
            print("Stop")
            break