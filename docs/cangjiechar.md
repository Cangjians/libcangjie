## The CangjieChar structure

This is the basic currency unit in libcangjie. `CangjieChar`'s are what the
functions return when you want to find what character corresponds to a certain
Cangjie code.

The `CangjieChar` structure is defined as follows:

```c
struct CangjieChar {
    char     chchar[5];
    char     simpchar[5];
    char     code[6];
    uint32_t frequency;
};
```

The `chchar` member is the character that the user actually wants, and the
`code` member is its Cangjie code.

For example, in Cangjie, the character (`chchar`) "木" has the `code` "d".

The `simpchar` member is the Simplified Chinese equivalent character of
the character in `chchar` field.

1. If the character is not a Chinese character, it would be an empty string.

2. If the character is its own Simplified Chinese equivalent character,
this will be of the same value as `chchar`.

3. If the character only exists in Simplified Chinese, this will be the
same value as `chchar`.

4. If the character has a distinct Simplified Chinese equivalent character,
this will be that equivalent character. For example, the CangjieChar with
`chchar` equals to "後" has the `simpchar` "后". The one with `chchar`
equals to "木" has `simpchar` "木".

Finally, the `frequency` member is a useful measure to order the characters
when presenting them to the user. The higher it is, the more frequent that
character is.

For example, a character with a `frequency` of 1000 should be presented before
a character with a frequency of 500.

#### Instantiating a CangjieChar: `cangjie_char_new()`

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
int ret = cangjie_char_new(&c, "木", "木", "d", 1000);
```

#### Freeing used memory: `cangjie_char_free()`

You are expected to free all `CangjieChar` instances you create. If `c` is a
pointer to a `CangjieChar` instance:

```c
int ret = cangjie_char_free(c);
```
