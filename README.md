# RTqueue
Multiple queue for Real-Time Systems

## Installation

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
