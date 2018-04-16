#!/usr/bin/env bash
echo "cd to folder"
cd DIT168Example &&
docker-compose down &&
echo "cd home"
cd .. &&
echo "rmi all v2v_autobuild images"
docker rmi -f v2v_autobuild:armhf &&
echo "docker load"
cat v2v_autobuild.tar | docker load &&
rm -f v2v_autobuild.tar
