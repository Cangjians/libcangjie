## Output filtering

Often when using libcangjie you will get lists of characters (for example,
which characters correspond to the code "d*d" ?).

It is possible to filter these lists so you only get the characters you are
interested in.

Once you include the `cangjie.h` header, you will be able to use the following
filters:

* Use `CANGJIE_FILTER_BIG5` if you are interested in the characters which are
  part of the Big 5 charset.
* Use `CANGJIE_FILTER_HKSCS` if you want the characters which are part of the
  Hong Kong Supplemental Character Set.
* Use `CANGJIE_FILTER_PUNCTUATION` to get the punctuation characters.
* Use `CANGJIE_FILTER_CHINESE` if you want all Chinese characters.
* Use `CANGJIE_FILTER_ZHUYIN` in order to get the characters part of Taiwan's
  Zhuyin/Bopomofo alphabet.
* Use `CANGJIE_FILTER_KANJI` for the Japanese Kanji characters.
* Use `CANGJIE_FILTER_KATAKANA` and you'll get the Japanese Katakana
  characters.
* Use `CANGJIE_FILTER_HIRAGANA` if the Japanese Hiragana matter to you.
* Finally, use `CANGJIE_FILTER_SYMBOLS` to get access to lots of miscellaneous
  symbols.

Note that these are bit flags. If you want more than one, just OR them
together.

For example, if you want the Big 5 and HKSCS characters, use:

```c
CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS
```
