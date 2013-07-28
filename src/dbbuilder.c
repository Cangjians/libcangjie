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


char *create_chars = "CREATE TABLE chars(char_index INTEGER PRIMARY KEY ASC,\n"
                     "                   chchar TEXT, trad_zh INTEGER,\n"
                     "                   simpl_zh INTEGER, big5 INTEGER,\n"
                     "                   hkscs INTEGER, zhuyin INTEGER,\n"
                     "                   kanji INTEGER, hiragana INTEGER,\n"
                     "                   katakana INTEGER, punct INTEGER,\n"
                     "                   symbol INTEGER,\n"
                     "                   classic_freq INTEGER);";
char *create_codes = "CREATE TABLE codes(char_index INTEGER, version INTEGER,\n"
                     "                   code TEXT);";
char *insert_chars = "INSERT INTO chars VALUES(%d, '%q', %d, %d, %d, %d,\n"
                     "                         %d, %d, %d, %d, %d, %d, %d);";
char *insert_codes = "INSERT INTO codes VALUES(%d, %d, '%q');";


void insert_line(sqlite3 *db, char *line, int i) {
    char *saveptr;
    char *query;
    char *code;

    // Parse the line
    char *chchar = strtok_r(line, " ", &saveptr);
    uint32_t trad_zh = atoi(strtok_r(NULL, " ", &saveptr));
    uint32_t simpl_zh = atoi(strtok_r(NULL, " ", &saveptr));
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
    uint32_t classic_freq = atoi(strtok_r(NULL, "\0", &saveptr));

    query = sqlite3_mprintf(insert_chars, i, chchar, trad_zh, simpl_zh, big5,
                            hkscs, zhuyin, kanji, hiragana, katakana, punct,
                            symbol, classic_freq);
    sqlite3_exec(db, query, NULL, NULL, NULL);
    sqlite3_free(query);

    // FIXME: This will fail if there are more than 2 codes
    if (strchr(cj3_codes, ',') != NULL) {
        code = strtok_r(cj3_codes, ",", &saveptr);
        query = sqlite3_mprintf(insert_codes, i, 3, code);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);

        code = strtok_r(NULL, "\0", &saveptr);
        query = sqlite3_mprintf(insert_codes, i, 3, code);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);
    } else {
        query = sqlite3_mprintf(insert_codes, i, 3, cj3_codes);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);
    }

    // FIXME: This will fail if there are more than 2 codes
    if (strchr(cj5_codes, ',') != NULL) {
        code = strtok_r(cj5_codes, ",", &saveptr);
        query = sqlite3_mprintf(insert_codes, i, 5, code);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);

        code = strtok_r(NULL, "\0", &saveptr);
        query = sqlite3_mprintf(insert_codes, i, 5, code);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);
    } else {
        query = sqlite3_mprintf(insert_codes, i, 5, cj5_codes);
        sqlite3_exec(db, query, NULL, NULL, NULL);
        sqlite3_free(query);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s TABLE_FILE DB_FILE\n", argv[0]);
        printf("\n");
        printf("Build DB_FILE out of TABLE_FILE.\n");

        return 1;
    }

    char *tablefile = argv[1];
    char *dbfile = argv[2];
    printf("Building database '%s' from table '%s'...\n", dbfile, tablefile);

    // Create the database
    sqlite3 *db;
    sqlite3_open_v2(dbfile, &db,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    sqlite3_exec(db, create_chars, NULL, NULL, NULL);
    sqlite3_exec(db, create_codes, NULL, NULL, NULL);

    FILE *table = fopen(tablefile, "r");

    char line[128];
    int len;
    int i = 1;

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

    fclose(table);
    sqlite3_close(db);

    return 0;
}
