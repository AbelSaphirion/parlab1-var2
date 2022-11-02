#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

enum MissingComponent: int;
void increaseCounter(int &c, std::mutex &counterMutex);
void smocker(int &c, int max_c, MissingComponent possession, MissingComponent &currentMissingComponent, std::mutex &counterMutex, std::mutex &smokeIterMutex);
#endif
