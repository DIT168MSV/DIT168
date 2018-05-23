cmake_minimum_required(VERSION 3.9)
project(remoteVisualisation)

set(CMAKE_CXX_STANDARD 11)

add_executable(remoteVisualisation
        src/automake-arm.sh
        src/bootstrap.min.css
        src/bootstrap.min.js
        src/Chart.js
        src/index.html
        src/jquery-3.2.1.slim.min.js
        src/libcluon-v0.0.73.js
        src/libcluon-viewer-0.01.js
        src/LICENSE
        src/loader.js
        src/messages.odvd
        src/moment-with-locales.min.js
        src/popper.min.js
        src/README.md
        src/signal_autorun-soft.sh
        src/speedguage.js
        src/style.css
        Dockerfile.amd64
        Dockerfile.signal-viewer
        Dockerfile.armhf
        readme.md)
