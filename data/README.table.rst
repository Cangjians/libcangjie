These are some details about the data in the ``table.txt`` file.

Legal
=====

The data in the ``table.txt`` file is hereby placed under the Public Domain,
in the hope that is is useful.

Sources
=======

This data was generated out of a few sources:

* The Unihan database from the Unicode consortium
* The Unicode specification
* The data from Wan Leung Wong's original libcangjie
* Some careful thought from the libcangjie2 team

Some of us are not native Chinese speakers. As such, the data might be
incomplete, or even incorrect.

If you find that this is the case, please help us making it better by
`filing bugs <http://TODO>`_.

Data Format
===========

The format of the data in this table is as follows:

* The first column is the actual character the user desires to input.
* The second column is a boolean (0 or 1) representing whether the character
  is a Chinese character.
* The third column is a boolean representing whether the character exists in
  the Big5 encoding.
* The fourth column is a boolean representing whether the character is part of
  the Hong Kong Supplemental Character Set (HKSCS).
* The fifth column is a boolean representing whether the character is part of
  the Taiwanese Bopomofo/Zhuyin alphabet.
* The sixth column is a boolean representing whether the character is part of
  the Japanese Kanji alphabet.
* The seventh column is a boolean representing whether the character is part
  of the Japanese Hiragana alphabet.
* The eigth column is a boolean representing whether the character is part of
  the Japanse Katakana alphabet.
* The ninth column is a boolean representing whether the character is a
  punctuation mark.
* The tenth column is a boolean representing whether the character is a
  miscellaneous symbol.
* The eleventh column is a comma-separated list of the possible input codes
  for the character in Cangjie version 3, or the string "NA" if the character
  does not have an input code in Cangjie version 3.
* The twelfth column is a comma-separated list of the possible input codes for
  the character in Cangjie version 5, or the string "NA".
* The thirteenth column is a short input code for the character, or the string
  "NA". This is mostly to provide a convenient shortcut for users to quickly
  input punctuation marks and/or symbols (e.g the user can type "," to get
  '、', or '?' to get '？').
* The fourteenth column is an integer corresponding to the desired ordering of
  the characters. Depending on the situation, it can be one of three things:
  * For characters which were part of the Big5 encoding, this value is based
    on their order in that encoding. It should be the same ordering as with
    the Cangjie input method on a popular operating system.
  * For characters which have a short input code (see above), this value is
    based on the ordering that the libcangjie2 authors thought would be
    appropriate.
  * For all other characters, it is 0.
