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


#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <gdsl.h>

#include "rules.h"
#include "symbols.h"

typedef struct object object;

/* An object could be a rule or a symbol of variable kind */
typedef enum
{
    OT_RULE,
    OT_VARIABLE
} object_type;

extern object*
object_alloc (object_type type, void* content);

extern void 
object_free (void* e);

extern ulong
object_get_num (object* o);

extern gdsl_list_t 
object_get_list (object* o);

extern object_type 
object_get_type (object* o);

extern symbol*
object_get_symbol (object* o);

extern rule*
object_get_rule (object* o);

#endif /* _OBJECTS_H_ */


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
