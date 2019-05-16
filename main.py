from car import Car
from vision import Vision
from camera import Camera
import cv2
import numpy as np

if __name__ == '__main__':
    #car = Car(18,12)
    vision = Vision(0.1)
    camera = Camera()
    
    #car.reset()

    while True:
        img ,depth = camera.getImages()
        img2 = img.copy()
        if depth is None:
            #car.stop()
            #car.reset()
            break

        ret = vision.processFrame(depth)
        print(ret)
        font = cv2.FONT_HERSHEY_SIMPLEX
        print(img.shape)
        if ret == 1:
            cv2.putText(img2,"BREAK",(90,120),font,1.5,(0,0,255),5)
        elif ret == 3:
            cv2.putText(img2,"STEER LEFT",(30,120),font,1.5,(0,0,255),5)
        elif ret == 2:
            cv2.putText(img2,"STEER RIGHT",(30,120),font,1.5,(0,0,255),5)
        else:
            cv2.putText(img2,"GO",(130,120),font,1.5,(0,255,0),5)
        cv2.imshow("depth",depth/np.max(depth))
        cv2.imshow("image",img2)
        key = cv2.waitKey(1)
        if key == 27:
            exit(0)
        '''if key == 119:
            car.start()
        elif key == 115:
            car.stop()
        elif key == 97:
            car.steer(-1)
        elif key == 100:
            car.steer(1)
        elif key == 27:
            #if ret:
            car.stop()
            car.reset()
            print("Stop")
            break'''