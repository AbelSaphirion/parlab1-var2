#ifndef FUNC_H
#define FUNC_H

#include <mutex>

enum MissingComponent: int{
	wait,
	paper,
	tabacco,
	match
};
void increaseCounter(int &c, std::mutex &counterMutex);
void smocker(int &c, int max_c, int &sequencer, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &smokeIterMutex);
void dealer(int &c, int max_c, int &sequencer, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex);
#endif
