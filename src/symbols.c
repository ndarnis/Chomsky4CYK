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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <gdsl.h>

#include "symbols.h"

struct symbol
{
    char* name;
    unsigned short int num;
    bool initial;
};

extern void*
symbol_alloc (void* e)
{
    symbol* s = (symbol*) malloc (sizeof (symbol));
    assert (s);
    
    s->name = (char*) malloc (1 + strlen ((char*) e));
    assert (s->name);
    
    strcpy (s->name, (char*) e);
    s->num = 0;
    s->initial = FALSE;
    
    return (void*) s;
}

extern void 
symbol_free (void* e)
{
    symbol* s = (symbol*) e;
    
    if (s->name)
    {
	free (s->name);
    }
    
    free (s);
}

extern void 
symbol_set_initial (symbol* s)
{
    s->initial = TRUE;
}

extern bool 
symbol_is_initial (symbol* s)
{
    if (s->initial)
    {
	return TRUE;
    }

    if (s->name[strlen(s->name)-1] == SYMB_EPSILON || s->name[strlen(s->name)-1] == SYMB_PLUS)
    {
	return FALSE;
    }
    
    return TRUE;
}

extern char*
symbol_get_name (symbol* s)
{
    return s->name;
}

extern unsigned long int 
symbol_get_num (symbol* s)
{
    return s->num;
}

extern void 
symbol_set_num (symbol* s, unsigned long int n)
{
    s->num = n;
}

extern int
symbol_names_compare (symbol* s1, symbol* s2)
{
    return strcmp (s1->name, s2->name);
}

extern bool 
symbol_is_terminal (symbol* s)
{
    if (symbol_is_union (s) || symbol_is_epsilon (s))
    {
	return FALSE;
    }
    
    return (s->name[0] >= 'A' && s->name[0] <= 'Z') ? FALSE : TRUE;
}

extern bool 
symbol_is_variable (symbol* s)
{
    if (symbol_is_union (s) || symbol_is_epsilon (s))
    {
	return FALSE;
    }
    
    return (s->name[0] >= 'A' && s->name[0] <= 'Z') ? TRUE : FALSE;
}

extern bool 
symbol_is_epsilon (symbol* s)
{
    return (s->name[0] == SYMB_EPSILON) ? TRUE : FALSE;
}

extern bool 
symbol_is_union (symbol* s)
{
    return (s->name[0] == '|') ? TRUE : FALSE;
}


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
