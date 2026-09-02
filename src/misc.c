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


#include <stdlib.h>
#include <string.h>

#include <gdsl.h>

#include "misc.h"
#include "rules.h"
#include "symbols.h"

extern long int 
symbols_compare (const gdsl_element_t e1, void* e2)
{
    rule* r = (rule*) e1;
    symbol* s1 = rule_get_symbol (r);
    symbol* s2 = (symbol*) e2;
    return symbol_names_compare (s1, s2);
}

extern gdsl_element_t 
number_alloc (void* e)
{
    unsigned long int* n = (unsigned long int*) malloc (sizeof (unsigned long int));
    memcpy (n, (unsigned long int*) e, sizeof (unsigned long int));
    return (void*) n;
}

extern void 
number_free (gdsl_element_t e)
{
    free ((unsigned long int*) e);
}

extern long int 
strings_compare (const gdsl_element_t e1, void* e2)
{
    return strcmp (symbol_get_name ((symbol*) e1), (char *) e2);
}         


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
