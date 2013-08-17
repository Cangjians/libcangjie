Dependencies
============

To build this library, you will need the following:

* a C compiler and library (we recommend GCC and the GNU LibC)
* the SQLite3 library and development headers

Install from a release tarball
==============================

.. note:: There are no release tarballs at this point.

From the root folder of the unpacked tarball, do the usual Autotools dance::

    $ ./configure
    $ make
    # make install

Install from a git snapshot
===========================

From the root folder of your Git clone::

    $ ./autogen.sh
    $ make
    # make install
