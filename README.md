![build status on master](https://travis-ci.org/DIT168MSV/DIT168.svg?branch=master)
[![License](https://img.shields.io/badge/license-GPL--3-blue.svg)](https://raw.githubusercontent.com/chrberger/libcluon/master/LICENSE [![Alpine (x86_64)](https://img.shields.io/badge/Alpine-x86__64-blue.svg
)](https://github.com/chrberger/libcluon/blob/gh-pages/alpine/v3.7/x86_64/Dockerfile#L19) [![Alpine (armhf)](https://img.shields.io/badge/Alpine-armhf-blue.svg
)](https://github.com/chrberger/libcluon/blob/gh-pages/alpine/v3.7/armhf/Dockerfile#L25)

DIT168
======
Industrial IT and Embedded Systems project

## About this project

In this project we are developing a miniature smart vehicle
- The deployment and packaging  is docker based.
- It should be able to communicate with other smart vehicles from other groups in this course.

## Getting Started

Follows these steps to clone, build and run the program

## Cloning

Clone the repository by running git clone in your desired directory: 

```
git clone https://github.com/DIT168MSV/DIT168.git
```

## Building and running the program

1. Make a new directory in the src folder called build:

```
cd src
mkdir build
```
2. Navigate to that directory:
```
cd build
```
3. Call cmake to set up the automated compiling:
```
cmake ..
```
4. Call make to build and compile the program:
```
make
```
5. Run the receiver cxx:
```
./dit168.Receiver
```
6. Open a new terminal window, navigate to your build folder, and run the sender cxx:
```
./dit168.Sender
```
7. Test the program communication by using sender to send numbers to the receiver.

### Docker build

Docker build should be built from outside the source folder:
```
docker build -t dit168.local -f src/Dockerfile .
docker build -t dit168.local-armhf -f src/Dockerfile.armhf .
```

## Github layout

- We have a master branch were we will add code when we tested it and made sure it follows our quality standards.
- We have a development branch for testing, debugging and implementation of new features. In this branch we perform pull request to make sure code quality is high in the branch.

## License

* Beause our project is supported by Libluon libraries which uses GNU lisence, This project is released under the terms of the GNU GPLv3 License - [![License: GPLv3](https://img.shields.io/badge/license-GPL--3-blue.svg
)](https://www.gnu.org/licenses/gpl-3.0.txt)

