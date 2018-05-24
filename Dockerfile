# docker run --rm -ti -v $PWD:/opt/sources alpine:3.7 /bin/sh
FROM alpine:3.7 AS builder
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
    cd old/ && \
    cp dit168.Sender /tmp && \
    cp dit168.Receiver /tmp && \
    cd ../src/ && \
    cp MSV.Main /tmp && \
    cp MSV.RC /tmp && \
    cd ../V2V-Protocol/ && \
    cp V2V.Service /tmp

# Deploy.
FROM alpine:3.7
MAINTAINER Group 8
RUN apk update && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/V2V.Service .
COPY --from=builder /tmp/MSV.Main .
COPY --from=builder /tmp/MSV.RC .
COPY --from=builder /tmp/dit168.Sender .
COPY --from=builder /tmp/dit168.Receiver .
CMD ["/bin/sh"]