## Debian Unstable / Sid

libcangjie is included in the default Debian repositories, so you can just
install it with `apt-get`, as the root user:

```
# apt-get install libcangjie2
```

Note that if you need the development headers, then you should also install
the `libcangjie2-dev` package.

## Fedora

libcangjie is included in the default Fedora repositories, so you can just
install it with `yum`:
```
$ sudo yum install libcangjie
```

Note that if you need the development headers, then you should also install
the `libcangjie-devel` package.

## Build from the sources

### Dependencies

To build this library, you will need the following:

* a C compiler and library (we recommend GCC and the GNU C library)
* the SQLite3 library and development headers

### Install from a release tarball

_**Note:** There are no release tarballs at this point._

From the root folder of the unpacked tarball, do the usual Autotools dance:

```
$ ./configure
$ make
$ sudo make install
```

### Install from Git

First, you need to clone the development repository:

```
$ git clone git://github.com/Cangjians/libcangjie
```

Then, from the root folder of the Git clone, do the usual Autotools dance:

```
$ ./autogen.sh
$ make
$ sudo make install
```
