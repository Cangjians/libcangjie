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

#include "cangjie.h"


Cangjie *cangjie_new(CangjieVersion version, CangjieFilter filter_flags) {
    Cangjie *cj = calloc(1, sizeof(Cangjie));

    cj->version = version;
    cj->filter_flags = filter_flags;

    return cj;
}

int cangjie_free(Cangjie *cj) {
    free(cj);

    return 0;
}
