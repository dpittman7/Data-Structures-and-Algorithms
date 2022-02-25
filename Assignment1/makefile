OBJS	= mydriver.o
SOURCE	= mydriver.cpp
HEADER	= tlist.h tlist.hpp tnode.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

mydriver.o: mydriver.cpp
	$(CC) $(FLAGS) mydriver.cpp -lcppunit


clean:
	rm -f $(OBJS) $(OUT)
