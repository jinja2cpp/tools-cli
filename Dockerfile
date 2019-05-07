FROM alpine:latest as builder

LABEL maintainer="Andrey Bronin <jonnib@yandex.ru>"

RUN apk update && \
    apk upgrade && \
    apk --update add \
#        alpine-sdk \
        g++ \
        build-base \
        cmake \
#        bash \
        libstdc++ \
#        git \
        linux-headers \
#        cppcheck \
        py-pip && \
        pip install conan && \
    rm -rf /var/cache/apk/*

COPY . /project
WORKDIR /project
RUN conan user
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN conan remote add manu https://api.bintray.com/conan/manu343726/conan-packages
RUN cmake -DCMAKE_BUILD_TYPE=Release . && make

FROM alpine:latest
COPY --from=builder /project/bin/jinja2cpp /jinja2cpp

RUN apk update && \
    apk upgrade && \
    apk --update add libstdc++ \
    rm -rf /var/cache/apk/*

ENTRYPOINT [ "/jinja2cpp" ]