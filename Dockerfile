FROM ubuntu:focal as builder
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && \
    apt install -y \
        git \
        wget \
        cmake \
        python3 \
        python3-pip \
        python3.8-venv && \
    apt remove -y cmake && \
    apt clean

ENV EMBEDDED_PROTO_BRANCH field-options-hack

WORKDIR /tmp

ADD ./docker/archives /tmp
RUN tar -xvf protobuf-3.17.3.tar.gz && \
    mkdir /opt/protobuf && \
    cp -r protobuf-3.17.3/* /opt/protobuf/

RUN wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz && \
    tar -xvf wasi-sdk-12.0-linux.tar.gz && \
    mkdir /opt/wasi-sdk && \
    cp -r wasi-sdk-12.0/* /opt/wasi-sdk

RUN cd /opt && \
    git clone --recursive https://github.com/koinos/EmbeddedProto.git --branch $EMBEDDED_PROTO_BRANCH

RUN wget https://github.com/Kitware/CMake/releases/download/v3.21.4/cmake-3.21.4-linux-x86_64.sh && \
    chmod +x cmake-3.21.4-linux-x86_64.sh && \
    yes | ./cmake-3.21.4-linux-x86_64.sh && \
    mkdir /opt/cmake && \
    cp -r /tmp/cmake-3.21.4-linux-x86_64/* /opt/cmake/ && \
    ln -s /opt/cmake/bin/* /usr/local/bin

ADD . /koinos-sdk
WORKDIR /koinos-sdk

ENV KOINOS_WASI_SDK_ROOT=/opt/wasi-sdk
ENV KOINOS_PROTOBUF_ROOT=/opt/protobuf
ENV KOINOS_EMBEDDED_PROTO_ROOT=/opt/EmbeddedProto

RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/opt/koinos-sdk/cpp .. && \
    make -j install

FROM ubuntu:focal
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && \
    apt install -y \
        python3 \
        python3-pip \
        python3.8-venv && \
    apt clean

COPY --from=builder /opt /opt

ADD ./docker/project /opt/koinos-sdk/cpp/project
ADD ./docker/scripts /opt/koinos-sdk/cpp/scripts

ENTRYPOINT [ "/opt/koinos-sdk/cpp/scripts/build.sh" ]
