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

std::mutex counter_mutex;
void increase_counter(int &c){
	std::lock_guard<std::mutex> guard(counter_mutex);
	c++;
}

std::mutex smoke_iter_mutex;
missing_component current_missing_component = wait;
void smocker(int &c, int max_c, missing_component possession){
	while(c < max_c){
		if(current_missing_component == possession){
			std::lock_guard<std::mutex> guard(smoke_iter_mutex);
			current_missing_component = wait;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Current iteration: " << c << std::endl;
			increase_counter(c);
		}
	}
}

int main(){
	return 0;
}
