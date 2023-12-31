# RTqueue
Multiple queue for Real-Time Systems.

In this repository you can find a set of classes that allow you to create a single or muplile static/linked queue for real-time purposes and It can be tuned with a FIFO or LIFO scheduler.

## Installation ptask library

Pull submodules sources:

```bash
git submodule update --init
```

Build and install the **ptask** library:

```bash
cd lib/ptask
mkdir build
cd build
sudo apt install -y liballegro4-dev
cmake ..
make
sudo make install
```

Now to use the library, compile the program with this options:

```bash
g++ example.cpp -o example lib/ptask/build/src/libptask.a -I lib/ptask/build/src/include -l pthread
```

To include ptask library in the code use:

```c
extern "C" {
    #include <ptask.h>
}
```

You are now able to run our example:

```bash
cd example
make
```

And our tests:

```bash
cd test
make
```

This is ours makefile:

```makefile
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
```

## Library Setup

To compile a new program with our library you can copy all header files in your project and compile It with your code.

## Documentation

Documentation is generated by **doxygen** tool. You can find it [here](doc).

## Performance 

We calculated the insertion and extraction times in an example case consisting of two writer threads and two reader threads based on a number of reads and writes equal to 100. You can find our results [here](test/times/).