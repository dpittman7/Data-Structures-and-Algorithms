OBJS	= bet.o main.o
SOURCE	= bet.cpp main.cpp
HEADER	= bet.h
OUT	= proj4.x
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bet.o: bet.cpp
	$(CC) $(FLAGS) bet.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
