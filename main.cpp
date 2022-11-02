#include "func.h"
#include <mutex>
#include <thread>

int main(){
	int counter = 0;
	constexpr int max_c = 20;
	std::mutex counterMutex;
	std::mutex smokeIterMutex;
	MissingComponent currentMissingComponent = Wait;
	int sequencer = 0;
	std::thread s1(smocker, std::ref(counter), max_c, std::ref(sequencer), MissingComponent(Paper), std::ref(currentMissingComponent), std::ref(smokeIterMutex));
	std::thread s2(smocker, std::ref(counter), max_c, std::ref(sequencer), MissingComponent(Tabacco), std::ref(currentMissingComponent), std::ref(smokeIterMutex));
	std::thread s3(smocker, std::ref(counter), max_c, std::ref(sequencer), MissingComponent(Match), std::ref(currentMissingComponent), std::ref(smokeIterMutex));
	std::thread d(dealer, std::ref(counter), max_c, std::ref(sequencer), std::ref(currentMissingComponent), std::ref(counterMutex), std::ref(smokeIterMutex));
	d.join();
	s1.join();
	s2.join();
	s3.join();
	return 0;
}
