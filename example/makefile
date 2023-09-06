CC = g++
CFLAG = -Wall
LIBPATH = ../lib/ptask/build/src
CLIB = $(LIBPATH)/libptask.a

SRC = $(wildcard *.cpp)
TAR = $(SRC:.cpp=)

all: $(TAR)

%: %.cpp
	$(CC) $(CFLAG) $< $(CLIB) -o $@ -I $(LIBPATH)/include -l pthread