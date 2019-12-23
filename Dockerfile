FROM ubuntu:disco as builder

LABEL maintainer="Andrey Bronin <jonnib@yandex.ru>"

RUN apt-get update && \
    apt-get install -y nano git build-essential cmake python3-pip && \
    pip3 install conan

RUN conan user
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN conan remote add flexferrum https://api.bintray.com/conan/flexferrum/conan-packages
RUN conan remote add martin https://api.bintray.com/conan/martinmoene/nonstd-lite

COPY . /project
WORKDIR /project

RUN conan install . --build=missing
RUN cmake -DCMAKE_BUILD_TYPE=Release . && make

FROM ubuntu:disco
COPY --from=builder /project/bin/jinja2cpp-cli /jinja2cpp

# RUN apk update && \
#     apk upgrade && \
#     apk --update add libstdc++ \
#     rm -rf /var/cache/apk/*

ENTRYPOINT [ "/jinja2cpp" ]
