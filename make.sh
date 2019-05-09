g++ -c Car.cpp
g++ -c Camera.cpp
g++ -c Vision.cpp
g++ -c main.cpp
g++ -lopencv_core -lopencv_imgproc -lopencv_highgui -o demo Car.o Camera.o Vision.o main.o