These are some details about the data in the ``table.txt`` file.

Legal
=====

The data in the ``table.txt`` file is hereby placed under the Public
Domain, in the hope that is is useful.

Sources
=======

This data was generated out of a few sources:

* The Unihan database from the Unicode consortium
* The Unicode specification
* The data from Wan Leung Wong's original libcangjie
* Some careful thought from the libcangjie team

Some of us are not native Chinese speakers. As such, the data might be
incomplete, or even incorrect.

If you find that this is the case, please help us making it better by
[filing bugs](https://github.com/Cangjians/libcangjie/issues).

Data Format
===========

The format of the data in this table is as follows:

1. The actual character the user desires to input.

2. The Simplified Chinese equivalent character of the actual
   character. For example, for the line where the actual
   character is "後", this field should be "后".

3. A boolean (0 or 1) representing whether the character is a
   Chinese character.

4. A boolean representing whether the character exists in the
   Big5 encoding.

5. A boolean representing whether the character is part of the
   Hong Kong Supplemental Character Set (HKSCS).

6. A boolean representing whether the character is part of the
   Taiwanese Bopomofo/Zhuyin alphabet.

7. A boolean representing whether the character is part of the
   Japanese Kanji alphabet.

8. A boolean representing whether the character is part of the
   Japanese Hiragana alphabet.

9. A boolean representing whether the character is part of the
   Japanese Katakana alphabet.

10. A boolean representing whether the character is a punctuation mark.

11. A boolean representing whether the character is a
    miscellaneous symbol.

12. A comma-separated list of the possible input codes for the
    character in Cangjie version 3, or the string "NA" if the character
    does not have an input code in Cangjie version 3.

13. A comma-separated list of the possible input codes for the
    character in Cangjie version 5, or the string "NA".

14. A short input code for the character, or the string "NA". This is
    mostly to provide a convenient shortcut for users to quickly
    input punctuation marks and/or symbols (e.g the user can type
    "," to get '、', or '?' to get '？').

15. An integer corresponding to the desired ordering of the characters.
    Depending on the situation, it can be one of three things:
  1. For characters which were part of the Big5 encoding, this value is
     based on their order in that encoding. It should be the same
     ordering as with the Cangjie input method on a popular operating
     system.
  2. For characters which have a short input code (see above), this
     value is based on the ordering that the libcangjie authors thought
     would be appropriate.
  3. For all other characters, it is 0.
