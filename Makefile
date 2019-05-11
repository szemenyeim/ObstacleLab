CXX=g++
CXXFLAGS=-I . -Wall -Wextra -Ofast -MD -ffast-math -march=native 
BUILD = bin

_OBJS = Camera.o Car.o Vision.o main.o
OBJS = $(addprefix $(BUILD)/,$(_OBJS))

DEPS = Camera.h Car.h Vision.h

LDFLAGS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lpigpio -lOpenNI

$(BUILD)/%.o: %.cpp
	@mkdir -p bin
	$(CXX) -c $< $(CXXFLAGS) -o $@

demo: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD)/demo

clean:
	rm -rf $(BUILD)

-include $(OBJS:.o=.d)
