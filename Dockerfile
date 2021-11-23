FROM koinos/koinos-cdt-toolchain:latest as builder

ADD . /koinos-cdt
WORKDIR /koinos-cdt

RUN cd $KOINOS_WASI_SDK_ROOT/bin && ls -la && cd /koinos-cdt && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/opt/koinos-cdt .. && \
    make -j install

FROM koinos/koinos-cdt-toolchain:latest
COPY --from=builder /opt/koinos-cdt /opt/koinos-cdt

ENV KOINOS_CDT_ROOT=/opt/koinos-cdt
ADD ./docker/ /opt

ENTRYPOINT [ "/opt/scripts/build.sh" ]
