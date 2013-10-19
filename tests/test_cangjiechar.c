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
#include <string.h>

#include <cangjie.h>


void test_cangjie_char_a() {
    char *chchar = "a";
    char *code = "abc";
    uint32_t frequency = 123;

    CangjieChar *c;
    int ret = cangjie_char_new(&c, chchar, code, frequency);
    assert(ret == CANGJIE_OK);

    assert(strcmp(c->chchar, chchar) == 0);
    assert(strcmp(c->code, code) == 0);
    assert(c->frequency == frequency);

    cangjie_char_free(c);
}

void test_cangjie_char_zh() {
    char *chchar = "\xE6\x9C\xA8"; // 木
    char *code = "abc";
    uint32_t frequency = 123;

    CangjieChar *c;
    int ret = cangjie_char_new(&c, chchar, code, frequency);
    assert(ret == CANGJIE_OK);

    assert(strcmp(c->chchar, chchar) == 0);
    assert(strcmp(c->code, code) == 0);
    assert(c->frequency == frequency);

    cangjie_char_free(c);
}


int main() {
    test_cangjie_char_a();
    test_cangjie_char_zh();
    return 0;
}
