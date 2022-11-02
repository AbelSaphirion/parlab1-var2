#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

enum MissingComponent: int{
	wait,
	tobacco,
	paper,
	match
};

void increaseCounter(int &c, std::mutex &counterMutex){
	std::lock_guard<std::mutex> guard(counterMutex);
	c++;
}

void smocker(int &c, int max_c, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex){
	while(c < max_c){
		if(currentMissingComponent == possession){
			std::lock_guard<std::mutex> guard(smokeIterMutex);
			currentMissingComponent = wait;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Current iteration: " << c << std::endl;
			increaseCounter(c, counterMutex);
		}
	}
}
