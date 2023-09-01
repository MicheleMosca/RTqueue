CC = g++
CFLAG = -Wall
CLIB = lib/ptask/src/ptask.c lib/ptask/src/pmutex.c lib/ptask/src/libdl.c lib/ptask/src/pbarrier.c lib/ptask/src/ptime.c lib/ptask/src/rtmode.c lib/ptask/src/tstat.c

SRC = $(wildcard *.cpp)
TAR = $(SRC:.cpp=)

all: $(TAR)

%: %.cpp
	$(CC) $(CFLAG) $< $(CLIB) -o $@ -Ilib/ptask/src -lpthread