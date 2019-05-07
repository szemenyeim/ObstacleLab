import numpy as np
import cv2

class Vision(object):
    def __init__(self,threshold):
        self.threshold = threshold

    def processFrame(self,frame):

        frame2 = frame[40:201].copy()

        frame2[frame2 == 0] = 20000

        _,bin = cv2.threshold(frame2,1000,1,cv2.THRESH_BINARY_INV)
        
        ratio = np.count_nonzero(bin)/bin.size
        print(ratio)

        if ratio > self.threshold:
            return True
        else:
            return False