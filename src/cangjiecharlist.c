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

#include "cangjiecharlist.h"
#include "cangjieerrors.h"


int cangjie_char_list_new_elem(CangjieCharList **l,
                               CangjieChar      *c) {
    CangjieCharList *tmp = calloc(1, sizeof(CangjieCharList));
    if (tmp == NULL) {
        return CANGJIE_NOMEM;
    }

    tmp->c = c;
    tmp->prev = NULL;
    tmp->next = NULL;

    *l = tmp;

    return CANGJIE_OK;
}

int cangjie_char_list_append(CangjieCharList **l,
                             CangjieChar      *c) {
    CangjieCharList *new_list;
    CangjieCharList *last;

    int ret = cangjie_char_list_new_elem(&new_list, c);
    if (ret != CANGJIE_OK) {
        return ret;
    }

    if (*l != NULL) {
        last = *l;
        while (last->next) {
            last = last->next;
        }

        last->next = new_list;
        new_list->prev = last;

        return CANGJIE_OK;
    }

    *l = new_list;

    return CANGJIE_OK;
}

int cangjie_char_list_prepend(CangjieCharList **l,
                              CangjieChar      *c) {
    CangjieCharList *new_list;

    int ret = cangjie_char_list_new_elem(&new_list, c);
    if (ret != CANGJIE_OK) {
        return ret;
    }

    if (*l != NULL) {
        (*l)->prev = new_list;
        new_list->next = *l;
    }

    *l = new_list;

    return CANGJIE_OK;
}

int cangjie_char_list_free(CangjieCharList *l) {
    if (l == NULL) {
        return CANGJIE_OK;
    }

    if (l->next != NULL) {
        cangjie_char_list_free(l->next);
    }
    cangjie_char_free(l->c);
    free(l);

    return CANGJIE_OK;
}
