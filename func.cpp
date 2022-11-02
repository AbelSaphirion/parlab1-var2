#include "func.h"
#include <thread>
#include <mutex>
#include <random>

void increaseCounter(int &c, std::mutex &counterMutex){
	std::lock_guard<std::mutex> guard(counterMutex);
	c++;
}

void smocker(int &c, int max_c, int &sequencer, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &smokeIterMutex){
	while(c < max_c){
		if(currentMissingComponent == possession){
			std::lock_guard<std::mutex> guard(smokeIterMutex);
			if(currentMissingComponent != possession) continue;
			sequencer++;
			currentMissingComponent = Wait;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

void dealer(int &c, int max_c, int &sequencer, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex){
	std::random_device r;
	std::mt19937 e(r());
	std::uniform_int_distribution gen(1, 3);
	for(; c < max_c; increaseCounter(c, counterMutex)){
		currentMissingComponent = MissingComponent(gen(e));
		while(sequencer == 0);
		std::lock_guard<std::mutex> guard(smokeIterMutex);
		sequencer = 0;
	}
}
