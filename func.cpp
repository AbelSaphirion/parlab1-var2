#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

enum missing_component: int{
	wait,
	tobacco,
	paper,
	match
};

void increase_counter(int &c, std::mutex &counter_mutex){
	std::lock_guard<std::mutex> guard(counter_mutex);
	c++;
}

void smocker(int &c, int max_c, missing_component possession, missing_component &current_missing_component, std::mutex &counter_mutex, std::mutex &smoke_iter_mutex){
	while(c < max_c){
		if(current_missing_component == possession){
			std::lock_guard<std::mutex> guard(smoke_iter_mutex);
			current_missing_component = wait;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Current iteration: " << c << std::endl;
			increase_counter(c, counter_mutex);
		}
	}
}
