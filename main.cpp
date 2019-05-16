#include "Car.h"
#include "Camera.h"
#include "Vision.h"
#include <iostream>


int main()
{
	Car car(18, 12);
	Camera camera;

        //car.start();
	bool started = true;
        int steered = 0;

	while (true)
	{
		cv::Mat depth = camera.getDepth();
		if (!depth.data)
		{
			car.reset();
			std::cout << "No frame" << std::endl;
			return -1;
		}

                int ret = findObstacle(depth, 0.1);

                //std::cout << ret << std::endl;

                /*switch (ret)
		{
		case 0:
                        if (!started || steered != 0)
			{
                                std::cout << "Started" << std::endl;
                                //car.start();
				started = true;
                                steered = 0;
			}
			break;
		case 1:
			if (started)
			{
                                std::cout << "Stopped" << std::endl;
                                //car.stop();
				started = false;
                                steered = 0;
			}
			break;
		case 2:
                        if (started && steered != -1)
			{
                                std::cout << "Steered: -1" << std::endl;
                                //car.steer(-1);
                                steered = -1;
			}
			break;
		case 3:
                        if (started && steered != 1)
			{
                                std::cout << "Steered: 1" << std::endl;
                                //car.steer(1);
                                steered = 1;
			}
			break;
                }*/

		char key = cv::waitKey(1);

		switch (key)
		{
		case 'w':
                        if (!started || steered != 0)
			{
                                std::cout << "Started" << std::endl;
				car.start();
				started = true;
                                steered = 0;
			}
			break;
		case 's':
			if (started)
			{
                                std::cout << "Stopped" << std::endl;
				car.stop();
				started = false;
                                steered = 0;
			}
			break;
		case 'a':
                        if (started && steered != -1)
			{
                                std::cout << "Steer" << std::endl;
				car.steer(-1);
                                steered = -1;
			}
			break;
		case 'd':
                        if (started && steered != 1)
			{
                                std::cout << "Steer" << std::endl;
				car.steer(1);
                                steered = 1;
			}
			break;
                case 27:
                        car.reset();
                        return 0;
			break;
		}
	}

	return 0;
}
