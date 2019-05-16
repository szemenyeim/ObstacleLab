import numpy as np
import cv2

class Vision(object):
    def __init__(self,threshold):
        self.threshold = threshold

    def processFrame(self,frame):

        frame2 = frame[:161].copy()

        frame2[frame2 == 0] = 20000

        _,bin = cv2.threshold(frame2,1000,1,cv2.THRESH_BINARY_INV)
        
        ratio = np.count_nonzero(bin)/bin.size
        
        cv2.imshow("bin",bin*65000)
        
        m = cv2.moments(bin,True)

        if ratio > self.threshold:
            x = m['m10']/m['m00']
            if x < 100:
                return 2
            elif x > 220:
                return 3
            return 1;            
        else:
            return 0