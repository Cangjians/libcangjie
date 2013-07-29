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


#include <stdlib.h>
#include <string.h>

#include "cangjie.h"
#include "utils.h"


#define BASE_QUERY "SELECT chchar, code, classic_freq\n" \
                   "FROM chars\n" \
                   "INNER JOIN codes on chars.char_index=codes.char_index\n" \
                   "WHERE version=%d "


char *cangjie_get_filter_query(Cangjie *cj) {
    char *query;

    if (cj->filter_flags == 0) {
        // No filter means pass all, so let's return an empty string
        query = calloc(1, sizeof(char));
        return query;
    }

    // Longest possible string has a length of 59:
    //     " AND ( big5 = 1 OR hkscs = 1 OR punct = 1 OR trad_zh = 1 ) "
    query = calloc(60, sizeof(char));
    uint32_t first = 1;

    strcat(query, " AND ( ");

    if (cj->filter_flags & CANGJIE_FILTER_BIG5) {
        strcat(query, "big5 = 1 ");
        first = 0;
    }

    if (cj->filter_flags & CANGJIE_FILTER_HKSCS) {
        if (first) {
            strcat(query, "hkscs = 1 ");
            first = 0;
        } else {
            strcat(query, "OR hkscs = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_PUNCTUATION) {
        if (first) {
            strcat(query, "punct = 1 ");
            first = 0;
        } else {
            strcat(query, "OR punct = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_TRADITIONAL) {
        if (first) {
            strcat(query, "trad_zh = 1 ");
            first = 0;
        } else {
            strcat(query, "OR trad_zh = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_SIMPLIFIED) {
        if (first) {
            strcat(query, "simpl_zh = 1 ");
            first = 0;
        } else {
            strcat(query, "OR simpl_zh = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_ZHUYIN) {
        if (first) {
            strcat(query, "zhuyin = 1 ");
            first = 0;
        } else {
            strcat(query, "OR zhuyin = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_KANJI) {
        if (first) {
            strcat(query, "kanji = 1 ");
            first = 0;
        } else {
            strcat(query, "OR kanji = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_KATAKANA) {
        if (first) {
            strcat(query, "katakana = 1 ");
            first = 0;
        } else {
            strcat(query, "OR katakana = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_HIRAGANA) {
        if (first) {
            strcat(query, "hiragana = 1 ");
            first = 0;
        } else {
            strcat(query, "OR hiragana = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_SYMBOLS) {
        if (first) {
            strcat(query, "symbol = 1 ");
            first = 0;
        } else {
            strcat(query, "OR symbol = 1 ");
        }
    }

    strcat(query, ") ");

    return query;
}

Cangjie *cangjie_new(CangjieVersion version, CangjieFilter filter_flags) {
    Cangjie *cj = calloc(1, sizeof(Cangjie));

    cj->version = version;
    cj->filter_flags = filter_flags;

    cj->base_query = calloc(strlen(BASE_QUERY), sizeof(char));
    strcat(cj->base_query, BASE_QUERY);

    char *filter_query = cangjie_get_filter_query(cj);
    append_string(&cj->base_query, filter_query);
    free(filter_query);

    sqlite3_open_v2(CANGJIE_DB, &cj->db, SQLITE_OPEN_READONLY, NULL);

    return cj;
}

int cangjie_free(Cangjie *cj) {
    sqlite3_close(cj->db);
    free(cj->base_query);
    free(cj);

    return 0;
}
