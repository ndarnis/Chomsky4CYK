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


#ifndef _RULES_H_
#define _RULES_H_

#include <gdsl.h>

#include "symbols.h"

typedef struct rule rule;

extern void*
rule_alloc (void* s);

extern void 
rule_free (void* e);

extern void
rule_write (void* e, FILE* f, gdsl_location_t l, void* d);

extern symbol*
rule_get_symbol (rule* r);

extern void 
rule_set_symbol (rule* r, symbol* s);

extern gdsl_list_t 
rule_get_production (rule* r);

extern unsigned long int 
rule_get_num (rule* r);

extern void 
rule_set_num (rule* r, unsigned long int n);

extern int
rule_get_right_member_length (rule* r);

extern void
rule_add_element (rule* r, gdsl_element_t e);

#endif /* _RULES_H_ */


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
