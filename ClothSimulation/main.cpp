
#include "ClothSimulation.h"
#include "Timer.h"
#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	std::cout << "Q, W, E, R to release cloth corners" << std::endl;
	Cloth::Timer timer;
	timer.startTimer();
	Cloth::ClothSimulation clothSimulation;
	while(true)
	{
		timer.stopTimer();
		double fElapsedTime = timer.getElapsedTimeInSeconds();
		timer.startTimer();
		clothSimulation.update(fElapsedTime);
		clothSimulation.render();
	}
	return 0;
}
