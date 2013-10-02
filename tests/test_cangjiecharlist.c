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


void test_cangjie_char_list_append() {
    CangjieCharList *l = NULL;

    /* Append the first node */
    CangjieChar *char1;
    CangjieChar *char2;
    int ret = cangjie_char_new(&char1, "森", "ddd", 123);
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_append(&l, char1);
    assert(ret == CANGJIE_OK);

    assert(l->c == char1);

    /* Append a new node */
    ret = cangjie_char_new(&char2, "明", "ab", 123);
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
    int ret = cangjie_char_new(&char1, "曝", "aate", 123);
    assert(ret == CANGJIE_OK);

    ret = cangjie_char_list_prepend(&l, char1);
    assert(ret == CANGJIE_OK);

    assert(l->c == char1);

    /* Prepend a new node */
    ret = cangjie_char_new(&char2, "鷳", "abhaf", 123);
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
}
