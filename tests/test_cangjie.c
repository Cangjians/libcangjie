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

#include <cangjie.h>


void test_cangjie_new() {
    Cangjie *cj = cangjie_new(CANGJIE_VERSION_3, CANGJIE_FILTER_TRADITIONAL);

    assert(cj->version == CANGJIE_VERSION_3);
    assert(cj->filter_flags == CANGJIE_FILTER_TRADITIONAL);

    cangjie_free(cj);
}


int main() {
    // FIXME: Can this be passed to all tests through some Autotools magic?
    setenv("CANGJIE_DB", CANGJIE_DB, 1);

    test_cangjie_new();
}
