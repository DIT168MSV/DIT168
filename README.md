![build status on master](https://travis-ci.org/DIT168MSV/DIT168.svg?branch=master)
![License](https://img.shields.io/badge/license-GPL--3-blue.svg)
[![Alpine (x86_64)](https://img.shields.io/badge/Alpine-x86__64-blue.svg)](https://github.com/chrberger/libcluon/blob/gh-pages/alpine/v3.7/x86_64/Dockerfile#L19)
[![Alpine (armhf)](https://img.shields.io/badge/Alpine-armhf-blue.svg
)](https://github.com/chrberger/libcluon/blob/gh-pages/alpine/v3.7/armhf/Dockerfile#L25)

DIT168
======
Industrial IT and Embedded Systems project partial fulfillment of Bsc Software engineering & management 2018

## About this project

In this project we are developing a miniature smart vehicle.
- The packaging and deployment of images with excutable binaries is done using docker.
- Miniature Car be able to communicate with other smart vehicles through V2V protocal.
- Emergency collision avoidance and Visualisation of exchange messages.

## Getting Started

Follows these steps to clone, build and run the program

## Cloning

Clone the repository by running git clone in your desired directory: 

```
git clone https://github.com/DIT168MSV/DIT168.git
```

## Building and running the program

1. Make a new directory into folderr of module you want to run: e.g

```
cd src
mkdir build
```
2. Navigate to that directory:
```
cd build
```
3. Type 'cmake' to set up the automated compiling:
```
cmake ..
```
4. Type 'make' to build and compile the program:
```
make
```
5. Run the modules locally as follows in the case of Remote control :
```
 ./MSV.RC --right=0.65 --left=0.6
```
6. Open a new terminal window, navigate to your build folder, and run the MSV.Main:
```
./MSV.Main
```
7. This procedure can be performed for all the directories on the repository.

### Docker build

Build docker images from outside the source folder till example one to run locally on x86_64 and armhf platforms respectively.

``
`$ docker build -t dit168.local -f Dockerfile .`\

`$ docker build -t dit168.local-armhf -f Dockerfile.armhf .`\

**These images can be  save and loaded by running ----

``
`$ docker save dit168.local > dit168.local.tar`\

`$ cat dit168.local.tar | docker load`

```
```
Otherwise we can build separate images for the modules using a python script ' automake-arm.sh' in oder to build and cross-compile the images into the miniature car and load the containers there.
```
cd src
automake-arm.sh

cd V2V-Protocal
automake-arm.sh
```
#### Docker run
In oder to run the docker containers use the script below;
```
docker run
    OR
 From our example codes of containers see below how to run
```
 `$ docker run --rm -ti --net=host signal-viewer:latest --cid=191`\
 `$ docker run --rm -ti --net=host autobuild:armhf`\
 `$ docker run --rm -ti --net=host v2v_autobuild:armhf`

```
Lastly make sure that these containers are stop or down if docker compose was used.
```
`$ docker ps`\
`$ docker stop <container id>`

``
## Github layout

- We have a master branch were we will add code when we tested it and made sure it follows our quality standards.
- We have a development branch for testing, debugging and implementation of new features. In this branch we perform pull request to make sure code quality is high in the branch. 

## License

* Beause our project is supported by Libluon libraries which uses GNU lisence, This project is released under the terms of the GNU GPLv3 License - [![License: GPLv3](https://img.shields.io/badge/license-GPL--3-blue.svg
)](https://www.gnu.org/licenses/gpl-3.0.txt)

