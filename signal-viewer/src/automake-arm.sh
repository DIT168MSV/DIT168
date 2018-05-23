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
docker build --rm -t signal_autobuild:armhf -f Dockerfile.armhf . &&
echo "Save as tar file"
docker save signal_autobuild:armhf > signal_autobuild.tar &&
echo "copy to beaglebone"
scp signal_autobuild.tar debian@192.168.8.1:~/ &&
rm -f signal_autobuild.tar &&

HELP=".HELP"

if [ $# -eq 0 ]
    then
        # run soft as default
        ssh debian@192.168.8.1 -t 'sh signal_autorun-soft.sh'
        exit 0
fi


# just run once
for i in "$1"
do
    case $i in
        -r|--run)
            ssh debian@192.168.8.1 -t 'sh autorun-run.sh'
        ;;
        -s|--soft)
            ssh debian@192.168.8.1 -t 'sh autorun-soft.sh'
        ;;
        *)
        #invalid arg
            echo "invalid argument: '$i'"
            cat $HELP
            exit 1
        ;;
    esac
done
