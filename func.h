#ifndef FUNC_H
#define FUNC_H

#include <mutex>

enum MissingComponent: int{
	Wait,
	Paper,
	Tabacco,
	Match
};
void increaseCounter(int &c, std::mutex &counterMutex);
void smocker(int &c, int max_c, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex);
void dealer(int &c, int max_c, MissingComponent &currentMissingComponent, std::mutex &smokeIterMutex);
#endif
