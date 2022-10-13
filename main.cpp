#include <iostream>
#include <thread>
#include <mutex>

enum missing_component: int{
	tobacco,
	paper,
	match
};

std::mutex counter_mutex;
void increase_counter(int &c){
	std::lock_guard<std::mutex> guard(counter_mutex);
	c++;
}


int main(){
	return 0;
}
