libcangjie is a very simple library:

* there is only one header to include: `cangjie.h`
* everything happens by instantiating a `Cangjie` context, and then passing it
  to the various functions of the API.

These pages will document proper use of libcangjie. Although the interesting
part is the last of the list, we recommend you read them in order:

1. the possible error codes (see errors.md)
2. the supported Cangjie versions (see versions.md)
3. the available output filters (see filters.md)
4. the `CangjieChar` structure (see cangjiechar.md)
5. the `CangjieCharList` character lists (see cangjiecharlist.md)
6. the `Cangjie` context (see cangjie.md)

libcangjie also comes with a command-line tool, which can be seen as an
example of how to use the API, and is useful for testing/debugging purpose:
`libcangjie_cli`. (see cli.md)
