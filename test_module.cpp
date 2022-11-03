#include "func.h"
#include <atomic>
#include <mutex>
#include <thread>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/included/unit_test.hpp>

int c = 0;
int c_max = 1;
std::mutex counterMutex;
std::mutex smokeIterMutex;
MissingComponent currentMissingComponent = Wait;
std::atomic<bool> done1(false);
std::atomic<bool> done2(false);
std::atomic<bool> done3(false);
std::atomic<bool> done4(false);
std::atomic<bool> done5(false);
std::atomic<bool> done6(false);

void smokeFunc(MissingComponent possession, std::atomic<bool> &done){
	done = false;
	smocker(c, c_max, possession, currentMissingComponent, counterMutex, smokeIterMutex);
	done = true;
}

void dealerFunc(std::atomic<bool> &done){
	done = false;
	dealer(c, c_max, currentMissingComponent, smokeIterMutex);
	done = true;
}

BOOST_AUTO_TEST_CASE(smokerWaitSmoke){
	c = 0;
	c_max = 1;
	currentMissingComponent = Wait;
	std::thread t(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == false);
	currentMissingComponent = Paper;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(currentMissingComponent == Wait);
	t.detach();
}

BOOST_AUTO_TEST_CASE(twoSmokersOneComponent){
	c = 0;
	c_max = 1;
	currentMissingComponent = Wait;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(smokeFunc, MissingComponent(Tabacco), std::ref(done2));
	BOOST_CHECK(done1 == false);
	BOOST_CHECK(done2 == false);
	currentMissingComponent = Paper;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	BOOST_CHECK(currentMissingComponent == Wait);
	t1.detach();
	t2.detach();
}