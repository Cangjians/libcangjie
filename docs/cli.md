## Name

libcangjie_cli - a CLI interface to the Cangjie database

## Synopsis

```
libcangjie_cli [OPTIONS] CODE
```

## Description

libcangjie_cli may be used to query the Cangjie database from the command
line.

This is mostly useful for testing and/or debugging purpose, as the primary
interface is through the libcangjie library.

## Options

The following options are understood:

* `-h`, `--help`
  
  Print a short help text and exit.

* `-f FILTER`, `--filter=FILTER`
  
  Specify a comma-separated list of filters to use for the query.
  
  Acceptable values are one or more of `big5`, `hkscs`, `punctuation`,
  `chinese`, `zhuyin`, `kanji`, `katakana`, `symbols`.
  
  The default is `big5,hkscs`.

* `-m MODE`, `--mode=MODE`
  
  Specify the query mode.
  
  Acceptable values are one of `code`, `shortcode` or `radical`.
  
  The default value is `code`.

* `-C VERSION`, `--cj-version=VERSION`
  
  Specify the Cangjie version to use for the query.
  
  Acceptable values are one of `3` or `5`.

## Exit status

On success, 0 is returned, a non-zero failure code otherwise.

See the `cangjie/cangjieerrors.h` header for the list of possible exit codes.

## Environment

As for libcangjie itself, the `CANGJIE_DB` environment variable can be used to
specify the full path to the Cangjie database.

## Exemples

To obtain the characters which have `a` for Cangjie code, with all default
options, run:

```
$ libcangjie_cli a
```

To obtain **all** the characters which have a Cangjie code starting with `h`
and ending with `i`, use:

```
$ libcangjie_cli --filter=big5,hkscs,punctuation,chinese,zhuyin,kanji,katakana,symbols 'd*d'
```

To get the Cangjie radical of the letter `x`, run:

```
$ libcangjie_cli --mode=radical x
```
