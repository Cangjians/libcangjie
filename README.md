This is a C library implementing the Cangjie input method.

Below is a trivial example of how to use it:

```c
#include <stdio.h>
#include <cangjie.h>

int main() {
    Cangjie *cj;
    int ret = cangjie_new(&cj, CANGJIE_VERSION_3,
                          CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS);
    CangjieCharList *chars;
    CangjieCharList *iter;
    ret = cangjie_get_characters(cj, "d*d", &chars);

    if (ret == CANGJIE_NOCHARS) {
        printf("No chars with code '%s'\n", "d*d");
        cangjie_free(cj);
        return 1;
    }

    iter = chars;

    while (1) {
        if (iter == NULL)
            break;

        printf("Char: %s, code: '%s', classic frequency: %d\n",
               iter->c->chchar, iter->c->code, iter->c->frequency);

        iter = iter->next;
    }

    cangjie_char_list_free(chars);
    cangjie_free(cj);
    return 0;
}
```

For more details, refer to the documentation, either
[online](http://cangjians.github.io/projects/libcangjie/documentation)
or the one shipped with this software.

Development happens [on github](https://github.com/Cangjians/libcangjie), and
stable release tarballs will be available when we reach that point.

## History

This library is based on
[Wan Leung Wong's original libcangjie](https://github.com/wanleung/libcangjie).

In fact, when writing it, we tried to stay close to the original libcangjie
API, because Wan Leung had done a pretty good job with it.

However, we felt the need to start afresh for a few reasons:

* due to real life constraints, Wan Leung didn't have any time to dedicate to
  libcangjie any more

* we felt that some of the technical decisions in the original libcangjie were
  not the wisest choice

Nevertheless, this library would probably not exist if Wan Leung hadn't opened
the way, so we feel it is important to give him credit.

Thank you very much Wan Leung!

## Legalities

libcangjie is offered under the terms of the
[GNU Lesser General Public License, either version 3 or any later version](http://www.gnu.org/licenses/lgpl.html).

We won't ask you to sign a copyright assignment or any other kind of silly and
tedious legal document, so just send us patches and/or pull requests!
