FROM alpine:3.7 as builder
MAINTAINER Group 8
RUN apk update && \
    apk --no-cache add \
        ca-certificates \
        cmake \
        g++ \
        make && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted
ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make && \
    cp V2V.Service /tmp

# Deploy.
FROM alpine:3.7
MAINTAINER Group 8
RUN apk update && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/V2V.Service .
