OBJS	= test_list.o
SOURCE	= test_list.cpp
HEADER	= List.h List.hpp
OUT	= proj2.x
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

test_list.o: test_list.cpp
	$(CC) $(FLAGS) test_list.cpp 


clean:
	rm -f $(OBJS) $(OUT)
