all: main test

main:
	g++ -pthread -g func.cpp main.cpp -o lab.o
test:
	g++ -pthread -lboost_unit_test_framework -g func.cpp test_module.cpp -o test.o
