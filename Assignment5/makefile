OBJS	= passserver.o proj5.o
SOURCE	= passserver.cpp proj5.cpp
HEADER	= hashtable.h hashtable.hpp passserver.h
OUT	= proj5.x
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = -lcrypt

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

passserver.o: passserver.cpp
	$(CC) $(FLAGS) passserver.cpp -lcrypt

proj5.o: proj5.cpp
	$(CC) $(FLAGS) proj5.cpp -lcrypt


clean:
	rm -f $(OBJS) $(OUT)
