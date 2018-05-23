#!/usr/bin/env bash
echo "cd to folder"
cd DIT168Example &&
docker-compose down &&
echo "cd home"
cd .. &&
echo "rmi all signal_autobuild images"
docker rmi -f signal_autobuild:armhf &&
echo "docker load"
cat signal_autobuild.tar | docker load &&
rm -f signal_autobuild.tar
