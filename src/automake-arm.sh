#!/usr/bin/env bash
# IMPORTANT
# YOU MUST RUN THIS SCRIPT INSIDE THE "src" FOLDER
# OR IT WILL NOT WORK!

# ASSUMES YOU ARE ON THE BEAGLEBONE NETWORK

###
# Build from armhf file
# save to tar file
# copy to car, home directory
##
echo "Building from Dockerfile.armhf"
docker build --rm -t autobuild:armhf -f Dockerfile.armhf . &&
echo "Save as tar file"
docker save autobuild:armhf > autobuild.tar &&
echo "copy to beaglebone"
scp autobuild.tar debian@192.168.8.1:~/ &&
rm -f autobuild.tar &&
ssh debian@192.168.8.1 -t 'sh autorun.sh'

