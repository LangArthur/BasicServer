# BasicServer
A basic server allowing tcp and udp connection with clients.

### Prerequisites

You'll need conan and cmake. Personnaly, I used conan version 1.20.3 and cmake version 3.13.4.

### Installing

First, you have to make a build directory for conan and cmake where you will install dependencies

```
mkdir build & cd build & conan install ..
```

Afetr that, run cmake

```
cmake ..
```

If you are on linux, run make
```
make
```
and you will find the executable in bin/

Else, if you are on windows, the programme is not yet compatible.

### Commandes list

All this command are available in the internal server shell :

```
$> shutdown
```
Stop the server

```
$> ports
```
Display Upd and Tcp local port.
After, it display all client ip and port connected with tcp.

## Running the tests

Tests are not available for now

## Built With

* [Conan](https://conan.io) - the C / C++ package manager
* [cmake](https://cmake.org) - a cross-platform tool for build, test and package software
* [Boost](https://www.boost.org) - a free peer-reviewed portable C++ soucre librairies


## Author

* **Arthur LANG** - *Initial work* - [LangArthur](https://github.com/LangArthur)

See also the list of [contributors](https://github.com/LangArthur/Image-Compressor/graphs/contributors) who participated in this project