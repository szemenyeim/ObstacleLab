import numpy as np
import cv2

class Vision(object):
    def __init__(self,threshold):
        self.threshold = threshold

    def processFrame(self,frame):

        frame = frame[40:201]

        frame[frame == 0] = 2000

        bin = cv2.threshold(frame,1000,1,cv2.THRESH_BINARY)

        if np.count_nonzero(bin)/bin.size > self.threshold:
            return True
        else:
            return False