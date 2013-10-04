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

#ifndef CANGJIECOMMON_H__
#define CANGJIECOMMON_H__

#ifdef __cplusplus
    #define CANGJIE_BEGIN_DECL extern "C" {
    #define CANGJIE_END_DECL }
#else
    #define CANGJIE_BEGIN_DECL
    #define CANGJIE_END_DECL
#endif

#if defined _WIN32
    #ifdef CANGJIE_DLLEXPORT
        #define CANGJIE_EXTERN __declspec(dllexport)
    #else
        #define CANGJIE_EXTERN __declspec(dllimport)
    #endif
    #define CANGJIE_INTERN
#elif __GNUC__ >= 4
    #define CANGJIE_EXTERN extern __attribute__((visibility("default")))
    #define CANGJIE_INTERN extern __attribute__((visibility("hidden")))
#else
    #define CANGJIE_EXTERN
    #define CANGJIE_INTERN
#endif

#endif
