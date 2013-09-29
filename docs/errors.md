---
layout: default
title: libcangjie2 documentation - Error codes
name: projects
project: libcangjie2
sub: doc
---

## Return values

**All functions in libcangjie2 return `int`'s**. Which value they return
depends on the success or failure of the execution.

When everything goes right, the function succeeds and returns `CANGJIE_OK`.

Functions which are supposed get you a list of characters will return
`CANGJIE_NOCHARS` when no characters correspond to your query.

If the libcangjie2 database could not be opened for some reason, then
`CANGJIE_DBOPEN` is returned.

If an error happens when querying the database, the function returns
`CANGJIE_DBERROR`.

When memory could not be allocated, the function will return `CANGJIE_NOMEM`.

Finally, functions will return `CANGJIE_INVALID` when they are passed an
invalid input.

Of course, you must include the `cangjie.h` header in order to have these
defined.
