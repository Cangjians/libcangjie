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


#include <stdlib.h>
#include <string.h>

#include "cangjie.h"


#define BASE_QUERY "SELECT chchar, code, frequency\n" \
                   "FROM chars\n" \
                   "INNER JOIN codes on chars.char_index=codes.char_index\n" \
                   "WHERE version=%d "

// Longest possible filter query has a length of 127:
//     " AND ( big5 = 1 OR hkscs = 1 OR punct = 1 OR ... ) "
#define MAX_LEN_FILTER_QUERY 127

// Longest possible code query has a length of 19:
//     "AND code GLOB '%q';"
#define MAX_LEN_CODE_QUERY 19


const char *cangjie_radicals[] = {
    "\xE6\x97\xA5", // 日
    "\xE6\x9C\x88", // 月
    "\xE9\x87\x91", // 金
    "\xE6\x9C\xA8", // 木
    "\xE6\xB0\xB4", // 水
    "\xE7\x81\xAB", // 火
    "\xE5\x9C\x9F", // 土
    "\xE7\xAB\xB9", // 竹
    "\xE6\x88\x88", // 戈
    "\xE5\x8D\x81", // 十
    "\xE5\xA4\xA7", // 大
    "\xE4\xB8\xAD", // 中
    "\xE4\xB8\x80", // 一
    "\xE5\xBC\x93", // 弓
    "\xE4\xBA\xBA", // 人
    "\xE5\xBF\x83", // 心
    "\xE6\x89\x8B", // 手
    "\xE5\x8F\xA3", // 口
    "\xE5\xB0\xB8", // 尸
    "\xE5\xBB\xBF", // 廿
    "\xE5\xB1\xB1", // 山
    "\xE5\xA5\xB3", // 女
    "\xE7\x94\xB0", // 田
    "\xE9\x9B\xA3", // 難
    "\xE5\x8D\x9C", // 卜
    "\xEF\xBC\xBA", // Ｚ
};

int cangjie_get_filter_query(Cangjie *cj, char **query) {
    uint32_t first = 1;
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
    char *filter_query;
    int ret;
    char *database_path;
    Cangjie *tmp = calloc(1, sizeof(Cangjie));
    if (tmp == NULL) {
        return CANGJIE_NOMEM;
    }

    tmp->version = version;
    tmp->filter_flags = filter_flags;

    // Prepare the main Cangjie query
    tmp->cj_query = calloc(strlen(BASE_QUERY) + MAX_LEN_FILTER_QUERY + 1,
                             sizeof(char));
    if (tmp->cj_query == NULL) {
        return CANGJIE_NOMEM;
    }

    strcat(tmp->cj_query, BASE_QUERY);

    ret = cangjie_get_filter_query(tmp, &filter_query);
    if (ret != CANGJIE_OK) {
        return ret;
    }

    strcat(tmp->cj_query, filter_query);
    free(filter_query);

    // Prepare the query by short code
    tmp->shortcode_query = calloc(strlen(BASE_QUERY) + MAX_LEN_CODE_QUERY + 1,
                                  sizeof(char));
    if (tmp->shortcode_query == NULL) {
        return CANGJIE_NOMEM;
    }

    strcat(tmp->shortcode_query, BASE_QUERY);
    strcat(tmp->shortcode_query, "AND code = '%q';");

    // Check the CANGJIE_DB env var (it is useful for local testing)
    database_path = getenv("CANGJIE_DB");
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
    char *cj_query;
    char *query_code;
    char *star_ptr;
    char *query;
    int ret;

    if (input_code == NULL || strlen(input_code) == 0 || strlen(input_code) > 5) {
        return CANGJIE_INVALID;
    }

    if (input_code[0] == '*' || input_code[strlen(input_code) - 1] == '*') {
        return CANGJIE_INVALID;
    }

    // Start with the Cangjie instance's cj_query
    cj_query = calloc(strlen(cj->cj_query) + MAX_LEN_CODE_QUERY + 1,
                      sizeof(char));
    if (cj_query == NULL) {
        return CANGJIE_NOMEM;
    }

    strcpy(cj_query, cj->cj_query);

    query_code = calloc(6, sizeof(char));
    if (query_code == NULL) {
        return CANGJIE_NOMEM;
    }
    strncpy(query_code, input_code, 5);

    // Handle optional wildcards
    star_ptr = strchr(query_code, '*');
    if (star_ptr == NULL) {
        strcat(cj_query, "AND code = '%q';");
    } else {
        strcat(cj_query, "AND code GLOB '%q';");
    }

    query = sqlite3_mprintf(cj_query, cj->version, query_code);
    if (query == NULL) {
        return CANGJIE_NOMEM;
    }

    ret = sqlite3_prepare_v2(cj->db, query, -1, &stmt, 0);
    if (ret != SQLITE_OK) {
        // FIXME: Unhandled error codes
        return ret;
    }

    free(query_code);
    free(cj_query);
    sqlite3_free(query);

    while (1) {
        ret = sqlite3_step(stmt);

        if (ret == SQLITE_ROW) {
            char *chchar = (char *)sqlite3_column_text(stmt, 0);
            char *code = (char *)sqlite3_column_text(stmt, 1);
            uint32_t frequency = (uint32_t)sqlite3_column_int(stmt, 2);

            CangjieChar *c;
            int ret = cangjie_char_new(&c, chchar, code, frequency);
            if (ret != CANGJIE_OK) {
                return ret;
            }

            ret = cangjie_char_list_prepend(&tmp, c);
            if (ret != CANGJIE_OK) {
                return ret;
            }
        } else if(ret == SQLITE_DONE) {
            // All rows finished
            sqlite3_finalize(stmt);
            break;
        } else {
            // Some error encountered
            return CANGJIE_DBERROR;
        }
    }

    if (tmp == NULL) {
        return CANGJIE_NOCHARS;
    }

    *l = tmp;

    return CANGJIE_OK;
}

int cangjie_get_characters_by_shortcode(Cangjie          *cj,
                                        char             *input_code,
                                        CangjieCharList **l) {
    CangjieCharList *tmp = NULL;

    sqlite3_stmt *stmt;
    int ret;
    char *query;

    if (input_code == NULL || strlen(input_code) != 1) {
        return CANGJIE_INVALID;
    }

    query = sqlite3_mprintf(cj->shortcode_query, 0, input_code);
    if (query == NULL) {
        return CANGJIE_NOMEM;
    }

    ret = sqlite3_prepare_v2(cj->db, query, -1, &stmt, 0);
    if (ret != SQLITE_OK) {
        // FIXME: Unhandled error codes
        return ret;
    }

    sqlite3_free(query);

    while (1) {
        ret = sqlite3_step(stmt);

        if (ret == SQLITE_ROW) {
            char *chchar = (char *)sqlite3_column_text(stmt, 0);
            uint32_t frequency = (uint32_t)sqlite3_column_int(stmt, 2);

            CangjieChar *c;
            int ret = cangjie_char_new(&c, chchar, input_code, frequency);
            if (ret != CANGJIE_OK) {
                return ret;
            }

            ret = cangjie_char_list_prepend(&tmp, c);
            if (ret != CANGJIE_OK) {
                return ret;
            }
        } else if(ret == SQLITE_DONE) {
            // All rows finished
            sqlite3_finalize(stmt);
            break;
        } else {
            // Some error encountered
            return CANGJIE_DBERROR;
        }
    }

    if (tmp == NULL) {
        return CANGJIE_NOCHARS;
    }

    *l = tmp;

    return CANGJIE_OK;
}

int cangjie_get_radical(Cangjie     *cj,
                        const char   key,
                        char       **radical) {
    if ((key < 'a' || key > 'z') && (key != '*')) {
        return CANGJIE_INVALID;
    }

    if (key == '*') {
        // Special case for the wildcard '*'
        *radical = "＊";
    } else {
        // The actual Cangjie radicals
        *radical = (char *)cangjie_radicals[key - 'a'];
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
    free(cj->cj_query);
    free(cj->shortcode_query);
    free(cj);

    return CANGJIE_OK;
}
