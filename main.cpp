#include "func.h"
#include <mutex>
#include <thread>

int main(){
	int counter = 0;
	constexpr int max_c = 5;
	std::mutex counterMutex;
	std::mutex smokeIterMutex;
	MissingComponent currentMissingComponent = Wait;
	std::thread s1(smocker, std::ref(counter), max_c, MissingComponent(Paper), std::ref(currentMissingComponent), std::ref(counterMutex), std::ref(smokeIterMutex));
	std::thread s2(smocker, std::ref(counter), max_c, MissingComponent(Tabacco), std::ref(currentMissingComponent), std::ref(counterMutex), std::ref(smokeIterMutex));
	std::thread s3(smocker, std::ref(counter), max_c, MissingComponent(Match), std::ref(currentMissingComponent), std::ref(counterMutex), std::ref(smokeIterMutex));
	std::thread d(dealer, std::ref(counter), max_c, std::ref(currentMissingComponent), std::ref(smokeIterMutex));
	d.join();
	s1.join();
	s2.join();
	s3.join();
	return 0;
}
