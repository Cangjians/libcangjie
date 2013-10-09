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

#include <assert.h>
#include <stdlib.h> // For the setenv function
#include <string.h>

#include <cangjie.h>

void set_env_var(const char *name, const char *value) {
#ifdef _WIN32
    char *buf = (char *)calloc(strlen(name) + strlen(value) + 2, 1);
    strcpy(buf, name);
    strcat(buf, "=");
    strcat(buf, value);
    _putenv(buf);
#else
    setenv(name, value, 1);
#endif
}

void test_cangjie_new() {
    Cangjie *cj;
    int ret = cangjie_new(&cj, CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    assert(ret == CANGJIE_OK);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_BIG5);

    cangjie_free(cj);
}


void test_cangjie_get_characters_single_result() {
    Cangjie *cj;
    CangjieCharList *l;
    int ret = cangjie_new(&cj, CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    assert(ret == CANGJIE_OK);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_BIG5);

    ret = cangjie_get_characters(cj, "dmlm", &l);
    assert(ret == CANGJIE_OK);

    assert(strcmp(l->c->chchar, "椏") == 0);
    assert(strcmp(l->c->code, "dmlm") == 0);
    assert(l->c->frequency == 10253);
    assert(l->next == NULL);

    cangjie_char_list_free(l);
    cangjie_free(cj);
}


void test_cangjie_get_characters_multiple_queries() {
    Cangjie *cj;
    CangjieCharList *l;
    CangjieCharList *l2;
    int ret = cangjie_new(&cj, CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    assert(ret == CANGJIE_OK);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_BIG5);

    ret = cangjie_get_characters(cj, "h*i", &l);
    assert(ret == CANGJIE_OK);
    cangjie_char_list_free(l);

    ret = cangjie_get_characters(cj, "dmlm", &l2);
    assert(ret == CANGJIE_OK);

    assert(strcmp(l2->c->chchar, "椏") == 0);
    assert(strcmp(l2->c->code, "dmlm") == 0);
    assert(l2->c->frequency == 10253);
    assert(l2->next == NULL);

    cangjie_char_list_free(l2);
    cangjie_free(cj);
}


int main() {
    // FIXME: Can this be passed to all tests through some Autotools magic?
    set_env_var("CANGJIE_DB", CANGJIE_DB);

    test_cangjie_new();
    test_cangjie_get_characters_single_result();
    test_cangjie_get_characters_multiple_queries();
    return 0;
}
