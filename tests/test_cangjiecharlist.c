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
#include <string.h>

#include <cangjie.h>


void test_cangjie_char_list_append() {
    CangjieCharList *l = NULL;

    /* Append the first node */
    CangjieChar *char1;
    CangjieChar *char2;
    int ret = cangjie_char_new(&char1, "\\xE6\\xA3\\xAE", "ddd", 123); // 森
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_append(&l, char1);
    assert(ret == CANGJIE_OK);

    assert(l->c == char1);

    /* Append a new node */
    ret = cangjie_char_new(&char2, "\\xE6\\x98\\x8E", "ab", 123); // 明
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_append(&l, char2);
    assert(ret == CANGJIE_OK);

    assert(l->c == char1);
    assert(l->next->c == char2);

    cangjie_char_list_free(l);
}

void test_cangjie_char_list_prepend() {
    CangjieCharList *l = NULL;

    /* Prepend the first node */
    CangjieChar *char1;
    CangjieChar *char2;
    int ret = cangjie_char_new(&char1, "\\xE6\\x9B\\x9D", "aate", 123); // 曝
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_prepend(&l, char1);
    assert(ret == CANGJIE_OK);

    assert(l->c == char1);

    /* Prepend a new node */
    ret = cangjie_char_new(&char2, "\\xE9\\xB7\\xB3", "abhaf", 123); // 鷳
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_prepend(&l, char2);
    assert(ret == CANGJIE_OK);

    assert(l->c == char2);
    assert(l->next->c == char1);

    cangjie_char_list_free(l);
}

int main() {
    test_cangjie_char_list_append();
    test_cangjie_char_list_prepend();
    return 0;
}
