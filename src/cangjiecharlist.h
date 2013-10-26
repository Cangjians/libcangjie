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

#ifndef CANGJIECHARLIST_H__
#define CANGJIECHARLIST_H__

#include "cangjiecommon.h"
#include "cangjiechar.h"


CANGJIE_BEGIN_DECL

typedef struct CangjieCharList CangjieCharList;
struct CangjieCharList {
    CangjieChar *c;
    CangjieCharList *prev;
    CangjieCharList *next;
};

CANGJIE_EXTERN int cangjie_char_list_append(CangjieCharList **l,
                             CangjieChar      *c);

CANGJIE_EXTERN int cangjie_char_list_prepend(CangjieCharList **l,
                              CangjieChar      *c);

CANGJIE_EXTERN int cangjie_char_list_free(CangjieCharList *l);

CANGJIE_END_DECL

#endif
