FROM cangjians/build-essential
MAINTAINER Cangjians (https://cangjians.github.io)

# basic environment for building
WORKDIR /usr/local/src/libcangjie

# copy source files to build
COPY "." "./"

# build the library
RUN echo -e "\n\nOS=$(cat /var/version)\n---------------\n" && \
  ./autogen.sh --prefix=/usr && \
  make && make install

ENTRYPOINT []
CMD ["make", "check", "distcheck"]
