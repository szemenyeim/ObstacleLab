#include "Car.h"
#include "Camera.h"
#include "Vision.h"
#include <iostream>


int main()
{
	Car car(18, 12);
	Camera camera;

	car.start();
	bool started = true;

	while (true)
	{
		cv::Mat depth = camera.getDepth();
		if (!depth.data)
		{
			car.reset();
			std::cout << "No frame" << std::endl;
			return -1;
		}

		switch (findObstacle(depth, 0.1))
		{
		case 0:
			if (!started)
			{
				car.start();
				started = true;
			}
			break;
		case 1:
			if (started)
			{
				car.stop();
				started = false;
			}
			break;
		case 2:
			if (started)
			{
				car.steer(-1);
			}
			break;
		case 3:
			if (started)
			{
				car.steer(1);
			}
			break;
		}

		char key = cv::waitKey(1);

		switch (key)
		{
		case 'w':
			if (!started)
			{
				car.start();
				started = true;
			}
			break;
		case 's':
			if (started)
			{
				car.stop();
				started = false;
			}
			break;
		case 'a':
			if (started)
			{
				car.steer(-1);
			}
			break;
		case 'd':
			if (started)
			{
				car.steer(1);
			}
			break;
		default:
			if (started)
			{
				car.reset();
				return 0;
			}
			break;
		}
	}

	return 0;
}