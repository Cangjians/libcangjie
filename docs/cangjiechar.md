---
layout: default
title: libcangjie2 documentation
name: projects
project: libcangjie2
sub: doc
---

## The CangjieChar structure

This is the basic currency unit in libcangjie2. `CangjieChar`'s are what the
functions return when you want to find what character corresponds to a certain
Cangjie code.

The `CangjieChar` structure is defined as follows:

```c
struct CangjieChar {
    char     chchar[5];
    char     code[6];
    uint32_t frequency;
};
```

The `chchar` member is the character that the user actually wants, and the
`code` member is its Cangjie code.

For example, in Cangjie, the character (`chchar`) "木" has the `code` "d".

Finally, the `frequency` member is a useful measure to order the characters
when presenting them to the user. The higher it is, the more frequent that
character is.

For example, a character with a `frequency` of 1000 should be presented before
a character with a frequency of 500.

#### Instanciating a CangjieChar: `cangjie_char_new()`

`CangjieChar`'s are really something that your application will consume, not
something you will create and manage.

Nevertheless, if you really want to create a new `CangjieChar`, use the
`cangjie_char_new` function:

* The first argument is the `chchar` member. It is a `char *` and must be
  less than 4 `char` in length.

* The second argument is the Cangjie `code` for this character. It is a
  `char *` and must be less that 5 `char` in length.

* The third argument is the `frequency` for this character. It is a `uint32_t`
  integer.

Here is an example:

```c
CangjieChar *c;
int ret = cangjie_char_new(&c, "木", "d", 1000);
```

#### Freeing used memory: `cangjie_char_free()`

You are expected to free all `CangjieChar` instances you create. If `c` is a
pointer to a `CangjieChar` instance:

```c
int ret = cangjie_char_free(c);
```
