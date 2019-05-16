import numpy as np
import cv2
from primesense import openni2
from primesense import _openni2 as c_api
import os.path as osp
from glob import glob1
import re

def tryint(s):
    try:
        return int(s)
    except:
        return s

def alphanum_key(s):
    """ Turn a string into a list of string and number chunks.
        "z23a" -> ["z", 23, "a"]
    """
    return [ tryint(c) for c in re.split('([0-9]+)', s) ]

class Camera(object):
    def __init__(self):
        openni2.initialize("/home/pi/Downloads/Linux/OpenNI-Linux-Arm-2.3/Redist")
        self.dev = openni2.Device.open_any()
        self.depth_stream = self.dev.create_depth_stream()
        self.color_stream = self.dev.create_color_stream()
        self.dev.set_depth_color_sync_enabled( True )
        self.depth_stream.start()
        self.depth_stream.set_video_mode(
            c_api.OniVideoMode(pixelFormat=c_api.OniPixelFormat.ONI_PIXEL_FORMAT_DEPTH_1_MM, resolutionX=320,
                               resolutionY=240, fps=30))
        self.color_stream.set_video_mode(
            c_api.OniVideoMode(pixelFormat=c_api.OniPixelFormat.ONI_PIXEL_FORMAT_RGB888, resolutionX=320,
                               resolutionY=240, fps=30))
        self.color_stream.start()
        self.dev.set_image_registration_mode(openni2.IMAGE_REGISTRATION_DEPTH_TO_COLOR)

    def getImages(self):
        dframe = self.depth_stream.read_frame()
        dframe_data = dframe.get_buffer_as_uint16()
        depth = np.frombuffer(dframe_data, dtype=np.uint16)
        depth.shape = (240, 320, 1)

        cframe = self.color_stream.read_frame()
        cframe_data = cframe.get_buffer_as_uint8()
        img = np.frombuffer(cframe_data, dtype=np.uint8)
        img.shape = (240, 320, 3)

        return np.fliplr(img), np.fliplr(depth)
