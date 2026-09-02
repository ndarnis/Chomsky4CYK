/*
 * This file is part of the Chomsky4CYK project [C4CYK].
 * Copyright (C) 1998-2026 Nicolas Darnis <ndarnis@free.fr>.
 *
 * C4CYK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * C4CYK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with C4CYK. If not, see <http://www.gnu.org/licenses/>. 
 */


#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <gdsl.h>

#define SYMB_EPSILON       '#'
#define SYMB_PLUS          '~'

typedef struct symbol symbol;

extern void*
symbol_alloc (void* e);

extern void 
symbol_free (void* e);

extern void 
symbol_set_initial (symbol* s);

extern bool 
symbol_is_initial (symbol* s);

extern char*
symbol_get_name (symbol* s);

extern unsigned long int 
symbol_get_num (symbol* s);

extern void
symbol_set_num (symbol* s, unsigned long int n);

extern int 
symbol_names_compare (symbol* s1, symbol* s2);

extern bool 
symbol_is_terminal (symbol* s);

extern bool 
symbol_is_variable (symbol* s);

extern bool 
symbol_is_epsilon (symbol* s);

extern bool 
symbol_is_union (symbol* s);

#endif /* _SYMBOLS_H_ */


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
