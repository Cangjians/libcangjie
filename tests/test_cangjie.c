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

    assert(strcmp(l->c->chchar, "\xE6\xA4\x8F") == 0); // 椏
    assert(strcmp(l->c->code, "dmlm") == 0);
    assert(l->c->frequency == 10253);
    assert(l->next == NULL);

    cangjie_char_list_free(l);
    cangjie_free(cj);
}


void test_cangjie_get_characters_results_order() {
    Cangjie *cj;
    CangjieCharList *l;
    CangjieCharList *cur;

    int ret = cangjie_new(&cj, CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    assert(ret == CANGJIE_OK);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_BIG5);

    ret = cangjie_get_characters(cj, "h*i", &l);
    assert(ret == CANGJIE_OK);

    cur = l;
    assert(strcmp(cur->c->chchar, "\xE5\x87\xA1") == 0); // 凡
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE4\xB9\x88") == 0); // 么
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE4\xB8\x9F") == 0); // 丟
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE5\xA4\x99") == 0); // 夙
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE8\x88\x9F") == 0); // 舟
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE5\x8D\xB5") == 0); // 卵
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE6\x88\x91") == 0); // 我
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE7\xA7\x81") == 0); // 私
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE7\x9A\x84") == 0); // 的
    assert(cur->next != NULL);

    cur = cur->next;
    assert(strcmp(cur->c->chchar, "\xE5\xBE\x85") == 0); // 待
    assert(cur->next != NULL);

    cangjie_char_list_free(l);
    cangjie_free(cj);
}


void test_cangjie_get_characters_by_shortcode() {
    Cangjie *cj;
    CangjieCharList *l;
    int ret = cangjie_new(&cj, CANGJIE_VERSION_3, CANGJIE_FILTER_BIG5);
    assert(ret == CANGJIE_OK);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_BIG5);

    ret = cangjie_get_characters_by_shortcode(cj, ",", &l);
    assert(ret == CANGJIE_OK);

    assert(strcmp(l->c->chchar, "\xEF\xB8\x91") == 0); // ︑
    assert(strcmp(l->c->code, ",") == 0);
    assert(l->c->frequency == 1);
    assert(l->next != NULL);

    assert(strcmp(l->next->c->chchar, "\xEF\xB8\x90") == 0); // ︐
    assert(strcmp(l->next->c->code, ",") == 0);
    assert(l->next->c->frequency == 0);
    assert(l->next->next != NULL);

    assert(strcmp(l->next->next->c->chchar, "\xEF\xBC\x8C") == 0); // ，
    assert(strcmp(l->next->next->c->code, ",") == 0);
    assert(l->next->next->c->frequency == 2);
    assert(l->next->next->next != NULL);

    assert(strcmp(l->next->next->next->c->chchar, "\xE3\x80\x81") == 0); // 、
    assert(strcmp(l->next->next->next->c->code, ",") == 0);
    assert(l->next->next->next->c->frequency == 3);
    assert(l->next->next->next->next == NULL);

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

    assert(strcmp(l2->c->chchar, "\xE6\xA4\x8F") == 0); // 椏
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
    test_cangjie_get_characters_results_order();
    test_cangjie_get_characters_by_shortcode();
    test_cangjie_get_characters_multiple_queries();
    return 0;
}
