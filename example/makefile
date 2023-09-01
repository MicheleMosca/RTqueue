CC = g++
CFLAG = -Wall
LIBPATH = ../lib/ptask/src
CLIB = $(LIBPATH)/ptask.c $(LIBPATH)/pmutex.c $(LIBPATH)/libdl.c $(LIBPATH)/pbarrier.c $(LIBPATH)/ptime.c $(LIBPATH)/rtmode.c $(LIBPATH)/tstat.c

SRC = $(wildcard *.cpp)
TAR = $(SRC:.cpp=)

all: $(TAR)

%: %.cpp
	$(CC) $(CFLAG) $< $(CLIB) -o $@ -I $(LIBPATH) -lpthread