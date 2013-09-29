---
layout: default
title: libcangjie2 documentation
name: projects
project: libcangjie2
sub: doc
---

## Lists of characters

This is again something your application will consume, but we document it here
both for reference, and because knowing how things work will provide you a
better understanding of how to use libcangjie2.

A `CangjieCharList` is merely a doubly-linked list of `CangjieChar` instances:

```c
struct CangjieCharList {
    CangjieChar *c;
    CangjieCharList *prev;
    CangjieCharList *next;
};
```

This is pretty self-explanatory: the `c` member is the `CangjieChar` of the
current item in the list, and the `prev` and `next` members are used to
iterate the list by reaching the previous or next item.

#### Growing a list: `cangjie_char_list_append()` and `cangjie_char_list_prepend()`

There are two ways to add elements to a list, you can either append a new
element at the end, or prepend a new element at the beginning.

Here again, the API is really trivial:

```c
// We have this list
CangjieCharList *l;

// Now create a new CangjieChar
CangjieChar *c;
int ret = cangjie_char_new(&c, "木", "d", 1000);

// And append it at the end of the list
ret = cangjie_char_list_append(&l, c);

// Or instead prepend it
ret = cangjie_char_list_prepend(&l, c);
```

**Note:** `cangjie_char_list_append()` has to traverse the entire list to find
the end, which is inefficient when repeatedly adding multiple items. It is
usually faster to prepend all the elements to the list.

#### Freeing used memory: `cangjie_char_list_free()`

You are responsible for freeing all the `CangjieCharList` you create. If `l`
is a pointer to a `CangjieCharList` instance:

```c
int ret = cangjie_char_list_free(l);
```

**Note:** `cangjie_char_list_free()` will traverse the list and free every
`CangjieChar` elements in it. You do not need to manually free them with
`cangjie_char_free()`.
