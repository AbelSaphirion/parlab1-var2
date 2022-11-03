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