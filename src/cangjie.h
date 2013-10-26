/* Copyright (c) 2013 - The libcangjie authors.
 *
 * This file is part of libcangjie.
 *
 * libcangjie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcangjie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcangjie.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CANGJIE_H__
#define CANGJIE_H__

#include <stdint.h>

#include <sqlite3.h>

#include "cangjiecommon.h"
#include "cangjiecharlist.h"
#include "cangjieerrors.h"


CANGJIE_BEGIN_DECL

typedef enum CangjieVersion {
    CANGJIE_VERSION_3 = 3,
    CANGJIE_VERSION_5 = 5,
} CangjieVersion;


typedef enum CangjieFilter {
    CANGJIE_FILTER_BIG5        = 1 << 0,
    CANGJIE_FILTER_HKSCS       = 1 << 1,
    CANGJIE_FILTER_PUNCTUATION = 1 << 2,
    CANGJIE_FILTER_CHINESE     = 1 << 3,
    CANGJIE_FILTER_ZHUYIN      = 1 << 4,
    CANGJIE_FILTER_KANJI       = 1 << 5,
    CANGJIE_FILTER_KATAKANA    = 1 << 6,
    CANGJIE_FILTER_HIRAGANA    = 1 << 7,
    CANGJIE_FILTER_SYMBOLS     = 1 << 8,
} CangjieFilter;


typedef struct Cangjie {
    uint32_t version;
    uint32_t filter_flags;

    sqlite3 *db;
    char *cj_query;
    char *shortcode_query;
} Cangjie;

CANGJIE_EXTERN int cangjie_new(Cangjie        **cj,
                CangjieVersion   version,
                CangjieFilter    filter_flags);

CANGJIE_EXTERN int cangjie_get_characters(Cangjie          *cj,
                           char             *code,
                           CangjieCharList **l);

CANGJIE_EXTERN int cangjie_get_characters_by_shortcode(Cangjie          *cj,
                                        char             *shortcode,
                                        CangjieCharList **l);

CANGJIE_EXTERN int cangjie_get_radical(Cangjie     *cj,
                        const char   key,
                        char       **radical);

CANGJIE_EXTERN int cangjie_is_input_key(Cangjie    *cj,
                         const char  key);

CANGJIE_EXTERN int cangjie_free(Cangjie *cj);

CANGJIE_END_DECL

#endif
