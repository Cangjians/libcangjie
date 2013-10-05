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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

#include "cangjieerrors.h"

#ifdef _WIN32
/*
 * public domain strtok_r() by Charlie Gordon
 *
 *   from comp.lang.c  9/14/2007
 *
 *      http://groups.google.com/group/comp.lang.c/msg/2ab1ecbb86646684
 *
 *     (Declaration that it's public domain):
 *      http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */

char* strtok_r(char *str, const char *delim, char **nextp) {
    char *ret;
    if (str == NULL)
        str = *nextp;
    str += strspn(str, delim);
    if (*str == '\0')
        return NULL;
    ret = str;
    str += strcspn(str, delim);
    if (*str)
        *str++ = '\0';
    *nextp = str;
    return ret;
}
#endif

char *create_chars = "CREATE TABLE chars(char_index INTEGER PRIMARY KEY ASC,\n"
                     "                   chchar TEXT UNIQUE, zh INTEGER,\n"
                     "                   big5 INTEGER, hkscs INTEGER,\n"
                     "                   zhuyin INTEGER, kanji INTEGER,\n"
                     "                   hiragana INTEGER, katakana INTEGER,\n"
                     "                   punct INTEGER, symbol INTEGER,\n"
                     "                   frequency INTEGER);";
char *create_codes = "CREATE TABLE codes(char_index INTEGER, version INTEGER,\n"
                     "                   code TEXT,\n"
                     "                   FOREIGN KEY(char_index) REFERENCES chars(char_index));";
char *insert_chars = "INSERT INTO chars VALUES(%d, '%q', %d, %d, %d, %d,\n"
                     "                         %d, %d, %d, %d, %d, %d);";
char *insert_codes = "INSERT INTO codes VALUES(%d, %d, '%q');";


int insert_line(sqlite3 *db, char *line, int i) {
    char *saveptr;
    char *query;
    char *code;

    // Parse the line
    char *chchar = strtok_r(line, " ", &saveptr);
    uint32_t zh = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t big5 = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t hkscs = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t zhuyin = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t kanji = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t hiragana = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t katakana = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t punct = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t symbol = atoi(strtok_r(NULL, " ", &saveptr));
    char *cj3_codes = strtok_r(NULL, " ", &saveptr);
    char *cj5_codes = strtok_r(NULL, " ", &saveptr);
    char *short_code = strtok_r(NULL, " ", &saveptr);
    uint32_t frequency = atoi(strtok_r(NULL, "\0", &saveptr));

    if (strcmp(short_code, "SPACE") == 0) {
        strcpy(short_code, " ");
    }

    if ((strcmp(cj3_codes, "NA") == 0) && (strcmp(cj5_codes, "NA") == 0) \
                                       && (strcmp(short_code, "NA") == 0)) {
        // This character is useless in the database
        return CANGJIE_OK;
    }

    query = sqlite3_mprintf(insert_chars, i, chchar, zh, big5, hkscs, zhuyin,
                            kanji, hiragana, katakana, punct, symbol,
                            frequency);
    if (query == NULL) {
        return CANGJIE_NOMEM;
    }

    sqlite3_exec(db, query, NULL, NULL, NULL);
    sqlite3_free(query);

    if (strcmp(cj3_codes, "NA") != 0) {
        code = strtok_r(cj3_codes, ",", &saveptr);
        while (code != NULL) {
            query = sqlite3_mprintf(insert_codes, i, 3, code);
            sqlite3_exec(db, query, NULL, NULL, NULL);
            sqlite3_free(query);
            code = strtok_r(NULL, ",", &saveptr);
        }
    }

    if (strcmp(cj5_codes, "NA") != 0) {
        code = strtok_r(cj5_codes, ",", &saveptr);
        while (code != NULL) {
            query = sqlite3_mprintf(insert_codes, i, 5, code);
            sqlite3_exec(db, query, NULL, NULL, NULL);
            sqlite3_free(query);
            code = strtok_r(NULL, ",", &saveptr);
        }
    }
    
    if (strcmp(short_code, "NA") != 0) {
        query = sqlite3_mprintf(insert_codes, i, 0, short_code);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);
    }

    return CANGJIE_OK;
}

int main(int argc, char **argv) {
    char *tablefile;
    char *dbfile;
    sqlite3 *db;
    FILE *table;
    char line[128];
    int len;
    int i = 1;

    if (argc != 3) {
        printf("Usage: %s TABLE_FILE DB_FILE\n", argv[0]);
        printf("\n");
        printf("Build DB_FILE out of TABLE_FILE.\n");

        return -1;
    }

    tablefile = argv[1];
    dbfile = argv[2];
    printf("Building database '%s' from table '%s'...\n", dbfile, tablefile);

    // Create the database
    sqlite3_open_v2(dbfile, &db,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
    sqlite3_exec(db, "BEGIN", NULL, NULL, NULL);
    sqlite3_exec(db, create_chars, NULL, NULL, NULL);
    sqlite3_exec(db, create_codes, NULL, NULL, NULL);

    table = fopen(tablefile, "r");

    while(fgets(line, 128, table) != NULL) {
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        len = strlen(line);

        if (line[len-1] == '\n') {
            line[len-1] = '\0';
            len -= 1;
        }

        insert_line(db, line, i);
        i += 1;
    }

    sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);

    fclose(table);

    sqlite3_exec(db, "CREATE INDEX i1 on codes(version, code);", NULL, NULL, NULL);

    sqlite3_close(db);

    return CANGJIE_OK;
}
