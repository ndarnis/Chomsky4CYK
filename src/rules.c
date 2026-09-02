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
#include <assert.h>

#include <gdsl.h>

#include "misc.h"
#include "rules.h"
#include "symbols.h"

struct rule
{
    symbol* symb;
    gdsl_list_t production;
    unsigned short int num;
};

extern void*
rule_alloc (void* s)
{
    rule* r = (rule*) malloc (sizeof (rule));
    assert (r);
    
    r->symb = s;
    r->production = gdsl_list_alloc (NULL, NULL, NULL);
    r->num = 0;
    
    return (void*) r;
}

extern void 
rule_free (void* e)
{
    rule* r = (rule*) e;
    gdsl_list_free (r->production);
    free (r);
}

extern void
rule_write (void* element, FILE* file, gdsl_location_t location, void* user_data)
{
    (void) location;

    rule* r = (rule*) element;
    symbol* symb = r->symb;
    char* name = symbol_get_name (symb);
    gdsl_list_t production = r->production;
    bool newline = *(bool*) user_data;
    symbol* s;
    gdsl_list_cursor_t cursor = gdsl_list_cursor_alloc (production);
    
    if (r->num == 0)
    {
	fprintf (file, "%s -> ", name);
    }
    else
    {
	fprintf (file, "R%-3d: %s -> ", r->num, name);
    }
    
    for (gdsl_list_cursor_move_to_head (cursor); (s = (symbol*) gdsl_list_cursor_get_content (cursor)); gdsl_list_cursor_step_forward (cursor))
    {
	fprintf (file, "%s ", symbol_get_name (s));
    }
    
    if (newline)
    {
	fprintf (file, "\n");
    }
    
    gdsl_list_cursor_free (cursor);
}

extern symbol*
rule_get_symbol (rule* r)
{
    return r->symb;
}

extern void 
rule_set_symbol (rule* r, symbol* s)
{
    r->symb = s;
}

extern gdsl_list_t 
rule_get_production (rule* r)
{
    return r->production;
}

extern unsigned long int 
rule_get_num (rule* r)
{
    return r->num;
}

extern void 
rule_set_num (rule* r, unsigned long int n)
{
    r->num = n;
}

extern int
rule_get_right_member_length (rule* r)
{
    gdsl_list_t l = rule_get_production (r);
    symbol* s = (symbol*) gdsl_list_get_head (l);
    
    if (symbol_is_epsilon (s)) return 0;
    
    return (int) gdsl_list_get_size (l);
}

extern void
rule_add_element (rule* r, gdsl_element_t e)
{
    gdsl_list_insert_tail (r->production, e);
}


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
