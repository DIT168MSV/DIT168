# DIT168
Industrial IT and Embedded Systems project

## About this project

In this project we are developing a miniature smart vehicle
- The deployment and packaging  is docker based.
- It should be able to communicate with other smart vehicles from other groups in this course.

## Getting Started

Follows these steps to clone, build and run the program

## Cloning

Simply clone our git repository by running this command into your terminal assuming that git is installed.
Otherwise go here and follow the commands [![Git](https://git-scm.com/downloads)](https://git-scm.com/downloads).

```
git clone https://github.com/DIT168MSV/DIT168.git
```

## Building and running the program

Start by creating a folder in the src folder (i.e mkdir build) in order to compile the cmakelist.txt then you automate
the compilation by calling make in that folder. Change directory to the build folder run cmake there as in the example
below. At last run the program oddEven.

```
cd Miniature/src
mkdir build
cd build
cmake ..
make
./ oddEven
```

## Github layout

- We have a master branch were we will add code when we tested it and made sure it follows our quality standards.
- We have a development branch for testing, debugging and implementation of new features. In this branch we shall
perform pull request to make sure code quality is high in the branch.
