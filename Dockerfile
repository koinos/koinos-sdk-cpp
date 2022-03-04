FROM koinos/koinos-sdk-toolchain:latest as builder

ADD . /koinos-sdk
WORKDIR /koinos-sdk

RUN cd $KOINOS_WASI_SDK_ROOT/bin && ls -la && cd /koinos-sdk && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/opt/koinos-sdk .. && \
    make -j install

FROM koinos/koinos-sdk-toolchain:latest
COPY --from=builder /opt/koinos-sdk /opt/koinos-sdk

ENV KOINOS_SDK_ROOT=/opt/koinos-sdk
ADD ./docker/ /opt

ENTRYPOINT [ "/opt/scripts/build.sh" ]
