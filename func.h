#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

enum missing_component: int;
void increase_counter(int &c, std::mutex &counter_mutex);
void smocker(int &c, int max_c, missing_component possession, missing_component &current_missing_component, std::mutex &counter_mutex, std::mutex &smoke_iter_mutex);
#endif
