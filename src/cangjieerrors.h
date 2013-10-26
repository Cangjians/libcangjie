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

#ifndef CANGJIEERRORS_H__
#define CANGJIEERRORS_H__
#define CANGJIE_OK       0  /* Successful result */
#define CANGJIE_NOCHARS  1  /* Nothing wrong, but no corresponding CangjieChar returned */
#define CANGJIE_DBOPEN   2  /* Could not open the database */
#define CANGJIE_DBERROR  3  /* Something happened when querying the database */
#define CANGJIE_NOMEM    4  /* Memory allocation failure */
#define CANGJIE_INVALID  5  /* Invalid input was passed to the library */

#endif
