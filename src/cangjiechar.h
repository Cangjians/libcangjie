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

#ifndef CANGJIECHAR_H__
#define CANGJIECHAR_H__

#include <stdint.h>
#include "cangjiecommon.h"


CANGJIE_BEGIN_DECL

typedef struct CangjieChar {
    char     chchar[5];
    char     simpchar[5];
    char     code[6];
    uint32_t frequency;
} CangjieChar;

CANGJIE_EXTERN int cangjie_char_new(CangjieChar **c,
                     const char   *chchar,
                     const char   *simpchar,
                     const char   *code,
                     uint32_t      frequency);

CANGJIE_EXTERN int cangjie_char_free(CangjieChar *c);

CANGJIE_END_DECL

#endif
