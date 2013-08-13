/* Copyright (c) 2013 - The libcangjie2 authors.
 *
 * This file is part of libcangjie2.
 *
 * libcangjie2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcangjie2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcangjie2.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>

#include <sqlite3.h>

#include "cangjiecharlist.h"
#include "cangjieerrors.h"


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
    char *base_query;
} Cangjie;

int cangjie_new(Cangjie        **cj,
                CangjieVersion   version,
                CangjieFilter    filter_flags);

int cangjie_get_characters(Cangjie          *cj,
                           char             *code,
                           CangjieCharList **l);

int cangjie_free(Cangjie *cj);
