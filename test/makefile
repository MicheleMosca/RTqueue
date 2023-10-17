CC = g++
CFLAG = -Wall
LIBPATH = ../lib/ptask/build/src
SRCPATH = ../src
CLIB = $(LIBPATH)/libptask.a

SRC = $(wildcard *.cpp)
TAR = $(SRC:.cpp=)

all: $(TAR)

%: %.cpp
	$(CC) $(CFLAG) $< $(CLIB) -o $@.o -I $(LIBPATH)/include -I $(SRCPATH) -l pthread

clean:
	rm -f *.o