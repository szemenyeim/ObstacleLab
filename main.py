from car import Car
from vision import Vision
from camera import Camera

if __name__ == '__main__':
    car = Car(18,12)
    vision = Vision(0.1)
    camera = Camera()

    car.start()

    while True:
        _ ,depth = camera.getImages()
        if depth is None:
            car.stop()
            car.reset()
            break

        ret = vision.processFrame(depth)
        if ret:
            car.stop()
            car.reset()
            break