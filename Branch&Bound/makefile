CC = gcc
CXX = g++
CFLAGS = -O3
CXXFLAGS = $(CFLAGS) -std=c++14 

TARGETS = hw4_bnb

.PHONY: all
all: $(TARGETS)

do:
	./hw4_bnb < open_501
	./hw4_bnb < open_502
	./hw4_bnb < open_503
	./hw4_bnb < open_1001
	./hw4_bnb < open_1002
	./hw4_bnb < open_1003
	./hw4_bnb < open_1501
	./hw4_bnb < open_1502
	./hw4_bnb < open_1503
	./hw4_bnb < open_2001
	./hw4_bnb < open_2002
	./hw4_bnb < open_2003
	./hw4_bnb < open_2501
	./hw4_bnb < open_2502
	./hw4_bnb < open_2503
	./hw4_bnb < open_3001
	./hw4_bnb < open_3002
	./hw4_bnb < open_3003
	./hw4_bnb < open_3501
	./hw4_bnb < open_3502
	./hw4_bnb < open_3503
	./hw4_bnb < open_4001
	./hw4_bnb < open_4002
	./hw4_bnb < open_4003

.PHONY: clean
clean:
	-rm -f $(TARGETS) $(TARGETS:=.o)

# Note: This is in POSIX standard. The syntax and executable file (without extension) may not be recognized by Microsoft Windows. You may need the Powershell stuff.

# example usage:
# 1. compile and yield an executable file
# 		$ make
# 2. execute the executable file and input testcases via stdin with "<" symbol
# 		$ ./hw4_bnb < open_20
# 3. clean files
# 		$ make clean