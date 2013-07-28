This is a library implementing the Cangjie input method.

Below is a trivial example of how to use it::

    // Note: The library doesn't exist yet, so take this as a target, it's
    //       what we'd like to end up with eventually.
    
    #include <cangjie.h>
    
    Cangjie *cj = cangjie_new(CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    CangjieCharList *chars = cj->get_characters("d*d");
    
    CangjieChar *c = chars->data;
    
    if (c == NULL) {
        printf("No chars with code 'd*d'\n");
        return 0;
    }
    
    while (1) {
        printf("Char: %s, code: '%s', classic frequency: %d\n",
               c->chchar, c->code, c->classic_freq);

        c = chars->next;
        if (c == NULL) {
            break;
        }
    }

For more details, refer to `the documentation`_.

Development, happens `on github`_, and stable release tarballs will be
available when we reach that point.

.. _the documentation: Sorry, not written yet. :(
.. _on github: Sorry, not pushed yet. :(

Installation instructions can be found in the ``INSTALL.rst`` file.

History
=======

This library is based on `Wan Leung Wong's libcangjie`_.

In fact, when writing it, we tried to preserve the original libcangjie API,
because Wan Leung had done a pretty good job with it.

However, we felt the need to start afresh for a few reasons:

* due to real life constraints, Wan Leung didn't have any time to dedicate to
  libcangjie any more

* we felt that some of the technical decisions in the original libcangjie were
  not the wisest choice

Nevertheless, this library would probably not exist if Wan Leung hadn't opened
the way, so we feel it is important to give him credit.

Thank you very much Wan Leung!

.. _Wan Leung Wong's libcangjie: https://github.com/wanleung/libcangjie

Legalities
==========

libcangjie2 is written by the folks listed in the ``AUTHORS`` file, who
decided to offer it under the
`GNU Lesser General Public License, either version 3 or any later version`_.

We won't ask you to sign a copyright assignment or any other kind of silly and
tedious legal document, so just send us patches and/or pull requests!

.. _GNU Lesser General Public License, either version 3 or any later version_: http://www.gnu.org/licenses/lgpl.html
