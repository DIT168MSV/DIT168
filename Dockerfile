FROM Alpine:3.7 as builder
MAINTAINER Jonathan Partain
RUN apk update && \
    apk --no-cache add \
    ca-certificates \
    make \
    cmake \
    g++ \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted

ADD . /opt/sources
WORKDIR /opt/sources
