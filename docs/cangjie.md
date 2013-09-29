## The Cangjie context

Now this is really the interesting part: it is the actual entry point to the
library. For everything worth doing with libcangjie2, you will want to get a
hold on a `Cangjie` context.

Here is how it is defined:

```c
struct Cangjie {
    uint32_t version;
    uint32_t filter_flags;

    sqlite3 *db;
    char *cj_query;
    char *shortcode_query;
};
```

The public members of the structure deserve some explanations:

* the `version` is an integer representing the version (see versions.md) of the
  Cangjie input method you are interested in.

* the `filter_flags` is an integer corresponding to how you want to
  filter the output (see filters.md) of the `cangjie_get_characters()` query
  function.

The remaining attributes are considered **private API** and should not be
accessed directly. As such, we will not document them here.

#### First step: get a Cangjie context with `cangjie_new()`

Because of the aforementioned private attributes, you **must** use the
`cangjie_new()` function as follows:

```c
Cangjie cj;
int ret = cangjie_new(&cj, 3, CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS);
```

The second parameter is one of the supported versions (see versions.md), and
the third is a bitwise OR of the available output filters (see filters.md).

These will have an impact on the `cangjie_get_characters()` query function.

Note that in the example above, given the output filters that have been used,
the only characters which would be returned are the ones which are part of the
Big 5 encoding and the Hong Kong Supplemental Character Set.

Output filters thus control the set of characters which will be returned, not
the ones which are filtered out.

#### Querying for characters

There are three query functions.

First, and most importantly, `cangjie_get_characters()` returns a list of
characters corresponding to a given Cangjie code.

This is really what is intended by a Cangjie input method: the user types an
input code, and expects one or more characters in return.

Here is an example of usage:

```c
CangjieCharList *l;

// cj is an initialized Cangjie context
int ret = cangjie_get_characters(cj, "abcd", &l);
```

After execution of the above, `l` will be a list (see cangjiecharlist.md) of
one or more `CangjieChar` instances (see cangjiechar.md) corresponding to the
"abcd" code in the Cangjie version passed to the constructor of the `Cangjie`
context.

Wildcards ("*") are supported inside a code. For example, the "d*d" code could
be used.

It is often desired to show the user the radical corresponding to the
characters they input, rather than (or along with) the latin letters they
actually type.

You can do that with the `cangjie_get_radical()` function, used as follows:

```c
char *radical;

// cj is an initialized Cangjie context
int ret = cangjie_get_radical(cj, 'd', &radical);
```

After execution, `radical` contains the radical corresponding to the 'd' code.

Finally, users (especiall Quick users) often want a convenient way to input
punctuation and symbols without knowing their Cangjie code.

As such, we provide the `cangjie_get_characters_by_shortcode()` function,
which is used in exactly the same way as the `cangjie_get_characters()` one:

```c
CangjieCharList *l;

int ret = cangjie_get_characters_by_shortcode(cj, ",", &l);
```

After execution, `l` would contain a `CangjieChar` instance for each
fullwidth / Chinese comma.

Note that in the above cases, you are expected to
free the `CangjieCharList` (see cangjiecharlist.md) that result from these
functions.

#### Validating user input

In your application, you might want to check whether the user input are valid
keys of Cangjie codes (to pass them to the `cangjie_get_characters()`
function), or not (for example, to pass other characters to the
`cangjie_get_characters_by_shortcode()` function).

You can do that with the `cangjie_is_input_key()` function:

```c
// ret would be equal to CANGJIE_OK here
int ret = cangjie_is_input_key(cj, "a");

// ret would be equal to CANGJIE_INVALID here
int ret = cangjie_is_input_key(cj, "@");
```

The function only returns either `CANGJIE_OK` (the key is a valid Cangjie
input) or `CANGJIE_INVALID` (the key is not).

#### Tidying up behind yourself

When done, you should destroy the `Cangjie` context to free the used memory
and closed the connection to the database:

```c
int ret = cangjie_free(cj);
```
