OBJS	= processor.o main.o
SOURCE	= processor.cpp main.cpp
HEADER	= processor.h
OUT	= proj6.x
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

processor.o: processor.cpp
	$(CC) $(FLAGS) processor.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
