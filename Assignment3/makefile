OBJS	= in2post.o
SOURCE	= in2post.cpp
HEADER	= stack.h stack.hpp
OUT	= 
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) $(OUT) $(LFLAGS)


in2post.o: in2post.cpp
	$(CC) $(FLAGS) in2post.cpp 


clean:
	rm -f $(OBJS) $(OUT)
