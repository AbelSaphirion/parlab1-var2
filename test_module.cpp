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

BOOST_AUTO_TEST_CASE(twoSmokersTwoComponents){
	c = 0;
	c_max = 2;
	currentMissingComponent = Wait;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(smokeFunc, MissingComponent(Tabacco), std::ref(done2));
	currentMissingComponent = Tabacco;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == false);
	BOOST_CHECK(done2 == false);
	BOOST_CHECK(currentMissingComponent == Wait);
	currentMissingComponent = Match;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == false);
	BOOST_CHECK(done2 == false);
	BOOST_CHECK(currentMissingComponent == Match);
	currentMissingComponent = Paper;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	BOOST_CHECK(currentMissingComponent == Wait);
	t1.detach();
	t2.detach();
}

BOOST_AUTO_TEST_CASE(c_maxLessThanC){
	c = 0;
	c_max = -1;
	currentMissingComponent = Wait;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(dealerFunc, std::ref(done2));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	t1.detach();
	t2.detach();
}

BOOST_AUTO_TEST_CASE(fullTest){
	c = 0;
	c_max = 3;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(smokeFunc, MissingComponent(Match), std::ref(done2));
	std::thread t3(smokeFunc, MissingComponent(Tabacco), std::ref(done3));
	std::thread t4(dealerFunc, std::ref(done4));
	std::this_thread::sleep_for(std::chrono::seconds(5));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	BOOST_CHECK(done3 == true);
	BOOST_CHECK(done4 == true);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
}

BOOST_AUTO_TEST_CASE(threeDealers){
	c = 0;
	c_max = 10;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(smokeFunc, MissingComponent(Match), std::ref(done2));
	std::thread t3(smokeFunc, MissingComponent(Tabacco), std::ref(done3));
	std::thread t4(dealerFunc, std::ref(done4));
	std::thread t5(dealerFunc, std::ref(done5));
	std::thread t6(dealerFunc, std::ref(done6));
	std::this_thread::sleep_for(std::chrono::seconds(15));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	BOOST_CHECK(done3 == true);
	BOOST_CHECK(done4 == true);
	BOOST_CHECK(done5 == true);
	BOOST_CHECK(done6 == true);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	t5.detach();
	t6.detach();
}

BOOST_AUTO_TEST_CASE(fiveSmokers){
	c = 0;
	c_max = 10;
	std::thread t1(smokeFunc, MissingComponent(Paper), std::ref(done1));
	std::thread t2(smokeFunc, MissingComponent(Match), std::ref(done2));
	std::thread t3(smokeFunc, MissingComponent(Tabacco), std::ref(done3));
	std::thread t4(smokeFunc, MissingComponent(Tabacco), std::ref(done4));
	std::thread t5(smokeFunc, MissingComponent(Match), std::ref(done5));
	std::thread t6(dealerFunc, std::ref(done6));
	std::this_thread::sleep_for(std::chrono::seconds(15));
	BOOST_CHECK(done1 == true);
	BOOST_CHECK(done2 == true);
	BOOST_CHECK(done3 == true);
	BOOST_CHECK(done4 == true);
	BOOST_CHECK(done5 == true);
	BOOST_CHECK(done6 == true);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	t5.detach();
	t6.detach();
}