FROM alpine:latest as builder

LABEL maintainer="Andrey Bronin <jonnib@yandex.ru>"

RUN apk update && \
    apk upgrade && \
    apk --update add \
#        alpine-sdk \
        g++ \
        build-base \
        cmake \
        libstdc++ \
        git \
        linux-headers \
        py-pip && \
        pip install conan && \
    rm -rf /var/cache/apk/*

COPY . /project
WORKDIR /project
RUN conan user
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN conan remote add andreybronin https://api.bintray.com/conan/andreybronin/conan
RUN conan remote add martinmoene https://api.bintray.com/conan/martinmoene/nonstd-lite
RUN conan install . --build=missing
RUN cmake -DCMAKE_BUILD_TYPE=Release . && make

FROM alpine:latest
COPY --from=builder /project/bin/jinja2cpp-cli /jinja2cpp

RUN apk update && \
    apk upgrade && \
    apk --update add libstdc++ \
    rm -rf /var/cache/apk/*

ENTRYPOINT [ "/jinja2cpp" ]
