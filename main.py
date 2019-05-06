from car import Car
from vision import Vision
from camera import Camera
import cv2

if __name__ == '__main__':
    car = Car(18,12)
    vision = Vision(0.1)
    camera = Camera()

    #car.start()

    while True:
        _ ,depth = camera.getImages()
        cv2.imshow("depth",depth)
        cv2.waitKey(1)
        if depth is None:
            #car.stop()
            #car.reset()
            break

        ret = vision.processFrame(depth)
        if ret:
            #car.stop()
            #car.reset()
            break