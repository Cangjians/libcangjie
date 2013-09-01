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


#define BASE_QUERY "SELECT chchar, code, classic_freq\n" \
                   "FROM chars\n" \
                   "INNER JOIN codes on chars.char_index=codes.char_index\n" \
                   "WHERE version=%d "

// Longest possible filter query has a length of 127:
//     " AND ( big5 = 1 OR hkscs = 1 OR punct = 1 OR ... ) "
#define MAX_LEN_FILTER_QUERY 127

// Longest possible code query has a length of 19:
//     "AND code LIKE '%q';"
#define MAX_LEN_CODE_QUERY 19


const char *cangjie_radicals[] = {
    ("日"), ("月"), ("金"), ("木"), ("水"), ("火"), ("土"),
    ("竹"), ("戈"), ("十"), ("大"), ("中"), ("一"), ("弓"),
    ("人"), ("心"), ("手"), ("口"), ("尸"), ("廿"), ("山"),
    ("女"), ("田"), ("難"), ("卜"), ("Ｚ")
};

int cangjie_get_filter_query(Cangjie *cj, char **query) {
    if (cj->filter_flags == 0) {
        // No filter means pass all, so let's return an empty string
        *query = calloc(1, sizeof(char));
        if (query == NULL) {
            return CANGJIE_NOMEM;
        }

        return CANGJIE_OK;
    }

    *query = calloc(MAX_LEN_FILTER_QUERY + 1, sizeof(char));
    if (query == NULL) {
        return CANGJIE_NOMEM;
    }

    uint32_t first = 1;

    strcat(*query, " AND ( ");

    if (cj->filter_flags & CANGJIE_FILTER_BIG5) {
        strcat(*query, "big5 = 1 ");
        first = 0;
    }

    if (cj->filter_flags & CANGJIE_FILTER_HKSCS) {
        if (first) {
            strcat(*query, "hkscs = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR hkscs = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_PUNCTUATION) {
        if (first) {
            strcat(*query, "punct = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR punct = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_CHINESE) {
        if (first) {
            strcat(*query, "zh = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR zh = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_ZHUYIN) {
        if (first) {
            strcat(*query, "zhuyin = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR zhuyin = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_KANJI) {
        if (first) {
            strcat(*query, "kanji = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR kanji = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_KATAKANA) {
        if (first) {
            strcat(*query, "katakana = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR katakana = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_HIRAGANA) {
        if (first) {
            strcat(*query, "hiragana = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR hiragana = 1 ");
        }
    }

    if (cj->filter_flags & CANGJIE_FILTER_SYMBOLS) {
        if (first) {
            strcat(*query, "symbol = 1 ");
            first = 0;
        } else {
            strcat(*query, "OR symbol = 1 ");
        }
    }

    strcat(*query, ") ");

    return CANGJIE_OK;
}

int cangjie_new(Cangjie        **cj,
                CangjieVersion   version,
                CangjieFilter    filter_flags) {
    Cangjie *tmp = calloc(1, sizeof(Cangjie));
    if (tmp == NULL) {
        return CANGJIE_NOMEM;
    }

    tmp->version = version;
    tmp->filter_flags = filter_flags;

    tmp->base_query = calloc(strlen(BASE_QUERY) + MAX_LEN_FILTER_QUERY + 1,
                             sizeof(char));
    if (tmp->base_query == NULL) {
        return CANGJIE_NOMEM;
    }

    strcat(tmp->base_query, BASE_QUERY);

    char *filter_query;
    int ret = cangjie_get_filter_query(tmp, &filter_query);
    if (ret != CANGJIE_OK) {
        return ret;
    }

    strcat(tmp->base_query, filter_query);
    free(filter_query);

    // Check the CANGJIE_DB env var (it is useful for local testing)
    char *database_path = getenv("CANGJIE_DB");
    if (database_path != NULL) {
        ret = sqlite3_open_v2(database_path, &tmp->db, SQLITE_OPEN_READONLY, NULL);
    } else {
        ret = sqlite3_open_v2(CANGJIE_DB, &tmp->db, SQLITE_OPEN_READONLY, NULL);
    }
    if (ret == SQLITE_CANTOPEN) {
        return CANGJIE_DBOPEN;
    } else if (ret != SQLITE_OK) {
        // FIXME: Unhandled error codes
        return ret;
    }

    *cj = tmp;

    return CANGJIE_OK;
}

int cangjie_get_characters(Cangjie          *cj,
                           char             *input_code,
                           CangjieCharList **l) {
    CangjieCharList *tmp = NULL;

    sqlite3_stmt *stmt;

    // Start with the Cangjie instance's base_query
    char *base_query = calloc(strlen(cj->base_query) + MAX_LEN_CODE_QUERY + 1,
                              sizeof(char));
    if (base_query == NULL) {
        return CANGJIE_NOMEM;
    }

    strcpy(base_query, cj->base_query);

    char *query_code = calloc(6, sizeof(char));
    if (query_code == NULL) {
        return CANGJIE_NOMEM;
    }
    strncpy(query_code, input_code, 5);

    // Handle optional wildcards
    char *star_ptr = strchr(query_code, '*');
    if (star_ptr == NULL) {
        strcat(base_query, "AND code = '%q';");
    } else {
        strcat(base_query, "AND code LIKE '%q';");
        query_code[star_ptr-query_code] = '%';
    }

    char *query = sqlite3_mprintf(base_query, cj->version, query_code);
    if (query == NULL) {
        return CANGJIE_NOMEM;
    }

    int ret = sqlite3_prepare_v2(cj->db, query, -1, &stmt, 0);
    if (ret != SQLITE_OK) {
        // FIXME: Unhandled error codes
        return ret;
    }

    free(query_code);
    free(base_query);
    sqlite3_free(query);

    while (1) {
        ret = sqlite3_step(stmt);

        if (ret == SQLITE_ROW) {
            char *chchar = (char *)sqlite3_column_text(stmt, 0);
            char *code = (char *)sqlite3_column_text(stmt, 1);
            uint32_t classic_freq = (uint32_t)sqlite3_column_int(stmt, 2);

            CangjieChar *c;
            int ret = cangjie_char_new(&c, chchar, code, classic_freq);
            ret = cangjie_char_list_prepend(&tmp, c);
        } else if(ret == SQLITE_DONE) {
            // All rows finished
            sqlite3_finalize(stmt);
            break;
        } else {
            // Some error encountered
            return CANGJIE_DBERROR;
        }
    }

    *l = tmp;

    return CANGJIE_OK;
}

int cangjie_get_radical(Cangjie     *cj,
                        const char   key,
                        const char **radical) {
    if ((key < 'a' || key > 'z') && (key != '*')) {
        return CANGJIE_INVALID;
    }

    if (key == '*') {
        // Special case for the wildcard '*'
        *radical = "＊";
    } else {
        // The actual Cangjie radicals
        *radical = cangjie_radicals[key - 'a'];
    }

    return CANGJIE_OK;
}

int cangjie_is_input_key(Cangjie    *cj,
                         const char  key) {
    if (key < 'a' || key > 'z') {
        return CANGJIE_INVALID;
    }

    return CANGJIE_OK;
}

int cangjie_free(Cangjie *cj) {
    sqlite3_close(cj->db);
    free(cj->base_query);
    free(cj);

    return CANGJIE_OK;
}
