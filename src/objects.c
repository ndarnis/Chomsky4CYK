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

#include "objects.h"
#include "rules.h"
#include "symbols.h"
#include "misc.h"

struct object
{
    object_type type;
    ulong num;
    union /* An object could be a rule or a symbol of variable kind */
    {
	symbol* s;
	rule* r;
    } u;
    gdsl_list_t list;
};

extern object*
object_alloc (object_type type, void* content)
{
    object* o = (object*) malloc (sizeof (object));
    assert (o);
    
    if (type == OT_RULE)
    {
	o->u.r = (rule*) content;
	o->num = rule_get_num (o->u.r);
    }
    
    if (type == OT_VARIABLE)
    {
	o->u.s = (symbol*) content;
	o->num = symbol_get_num (o->u.s);
    }
    
    o->type = type;
    o->list = gdsl_list_alloc (NULL, number_alloc, number_free);
    
    return o;
}

extern void 
object_free (void* e)
{
    object* o = (object*) e;
    gdsl_list_free (o->list);
    free (o);
}

extern ulong 
object_get_num (object* o)
{
    return o->num;
}

extern gdsl_list_t 
object_get_list (object* o)
{
    return o->list;
}

extern object_type 
object_get_type (object* o)
{
    return o->type;
}

extern symbol*
object_get_symbol (object* o)
{
    return o->u.s;
}

extern rule*
object_get_rule (object* o)
{
    return o->u.r;
}


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
