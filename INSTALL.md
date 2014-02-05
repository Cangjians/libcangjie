## Arch Linux

libcangjie has not been included in official repository yet, but only in AUR.
If it works for you and you like it, please don't hesitate to vote it on
[upvote it](https://aur.archlinux.org/packages/libcangjie/). You can install it
with `yaourt`:

```
$ yaourt libcangjie
```

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

## Ubuntu 14.04

libcangjie is included in the default Ubuntu repositories, **starting with the
14.04 release**, so you can install it with `apt-get`:

```
$ sudo apt-get install libcangjie2
```

Note that if you need the development headers, then you should also install
the `libcangjie2-dev` package.

## NixOS

libcangjie is included in the default NixOS channel, **starting with the
14.02 release**, so you can install it with `nix-env`:

```
$ nix-env --install libcangjie
```

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
