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

#define CANGJIE_OK       0  /* Successful result */
#define CANGJIE_NOCHARS  1  /* Nothing wrong, but no corresponding CangjieChar returned */
#define CANGJIE_DBOPEN   2  /* Could not open the database */
#define CANGJIE_DBERROR  3  /* Something happened when querying the database */
#define CANGJIE_NOMEM    4  /* Memory allocation failure */
#define CANGJIE_INVALID  5  /* Invalid input was passed to the library */
