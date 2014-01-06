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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cangjie.h>

#ifdef _MSC_VER
#define snprintf sprintf_s
#endif

void iterate_results(CangjieCharList *chars) {
    CangjieCharList *iter = chars;
    while (1) {
        if (iter == NULL) {
            break;
        }

        iter = iter->next;
    }
}

int main(int argc, char **argv) {
    Cangjie *cj;
    char i, j;
    char *code;
    uint32_t count = 0;
    clock_t cStartClock;

    int ret = cangjie_new(&cj, CANGJIE_VERSION_3,
                          CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS);
    if (ret == CANGJIE_DBOPEN) {
        printf("Could not open the Cangjie database\n");
        return ret;
    } else if (ret != CANGJIE_OK) {
        printf("Unhandled error while creating the Cangjie object: %d\n", ret);
        return ret;
    }

    code = malloc(4 * sizeof(char));

    printf("Testing all one-letter codes... ");
    cStartClock = clock();
    for (i = 97; i <= 122; i++) {
        CangjieCharList *chars = NULL;

        snprintf(code, 2, "%c", i);

        ret = cangjie_get_characters(cj, code, &chars);

        if (ret != CANGJIE_NOCHARS) {
            iterate_results(chars);

            cangjie_char_list_free(chars);
        }

        count++;
    }
    printf("Ran %d queries in %4.3f milliseconds\n", count,
           1000 * (clock() - cStartClock) / (double)CLOCKS_PER_SEC);

    count = 0;

    printf("Testing all two-letters codes... ");
    cStartClock = clock();
    for (i = 97; i <= 122; i++) {
        for (j = 97; j <= 122; j++) {
            CangjieCharList *chars = NULL;

            snprintf(code, 3, "%c%c", i, j);

            ret = cangjie_get_characters(cj, code, &chars);

            if (ret != CANGJIE_NOCHARS) {
                iterate_results(chars);

                cangjie_char_list_free(chars);
            }

            count++;
        }
    }
    printf("Ran %d queries in %4.3f milliseconds\n", count,
           1000 * (clock() - cStartClock) / (double)CLOCKS_PER_SEC);

    count = 0;

    printf("Testing all 'X*Y' codes... ");
    cStartClock = clock();
    for (i = 97; i <= 122; i++) {
        for (j = 97; j <= 122; j++) {
            CangjieCharList *chars = NULL;

            snprintf(code, 4, "%c*%c", i, j);

            ret = cangjie_get_characters(cj, code, &chars);

            if (ret != CANGJIE_NOCHARS) {
                iterate_results(chars);

                cangjie_char_list_free(chars);
            }

            count++;
        }
    }
    printf("Ran %d queries in %4.3f milliseconds\n", count,
           1000 * (clock() - cStartClock) / (double)CLOCKS_PER_SEC);

    cangjie_free(cj);
    free(code);

    return CANGJIE_OK;
}
