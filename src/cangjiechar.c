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


#include <stdlib.h>
#include <string.h>

#include "cangjiechar.h"


CangjieChar *cangjie_char_new(const char *chchar,
                              const char *code,
                              uint32_t    classic_freq) {
    CangjieChar *c = calloc(1, sizeof(CangjieChar));

    // Copy at most 4 bytes, it's a single UTF-8 encoded character
    strncpy(c->chchar, chchar, 4);

    // Copy at most 5 bytes, that's the longest a Cangjie input code can be
    strncpy(c->code, code, 5);

    c->classic_freq = classic_freq;

    return c;
}

int cangjie_char_free(CangjieChar *c) {
    free(c);

    return 0;
}
