all: main test

main:
	g++ -g func.cpp main.cpp -o lab.o
test:
	g++ -g func.cpp test_module.cpp -o test.o
