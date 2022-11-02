#include "func.h"
#include <thread>
#include <mutex>
#include <random>

void increaseCounter(int &c, std::mutex &counterMutex){
	std::lock_guard<std::mutex> guard(counterMutex);
	c++;
}

void smocker(int &c, int max_c, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex){
	while(c < max_c){
		if(currentMissingComponent == possession){
			std::lock_guard<std::mutex> guard(smokeIterMutex);
			if(currentMissingComponent != possession) continue;
			currentMissingComponent = Wait;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			increaseCounter(c, counterMutex);
		}
	}
}

void dealer(int &c, int max_c, MissingComponent &currentMissingComponent, std::mutex &smokeIterMutex){
	std::random_device r;
	std::mt19937 e(r());
	std::uniform_int_distribution<int> gen(1, 3);
	while(c < max_c){
		if(currentMissingComponent == Wait){
			std::lock_guard<std::mutex> guard(smokeIterMutex);
			currentMissingComponent = MissingComponent(gen(e));
		}
	}
}
