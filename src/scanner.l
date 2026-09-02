%{
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

#include "scanner.h"
#include "parser.h"
#include "parser.tab.h"
#include "main.h"
#include "symbols.h"

static int def_sets = 0, def_x = 0, def_v = 0;
static unsigned long int line_nb = 1;
static unsigned long int col_nb = 1;

static void count (void);
static int make_no_terminal (char* s);
static int make_terminal (char* s);

%}
%option nounput
%option noinput
%option noyywrap
%option case-sensitive

%array

comment                     ;.*

space                       [ \t]
spaces                      {space}*

or                          "|"
arrow                       "->"
epsilon                     "#"

digit                       [0-9]
letter                      [a-zA-Z_]

command                     "%"{space}

terminal                    [a-z+\-*/)(]|{digit}
non_terminal                [A-Z]({letter}|{digit})*

def_sets                    "ENSEMBLES"|"SETS"
def_grammar                 "GRAMMAIRE"|"GRAMMAR"

%%

{arrow}                     { count (); return ARROW; }
{or}                        { count (); return OR; }
{epsilon}                   { count (); return EPSILON; }

"X = {"                     { count (); if (def_v == 0) def_x = 1; }

"V = {"                     { count (); if (def_x == 0) def_v = 1; }
"}"                         { count ();
                              if (def_x == 1) def_x = 0; 
                              if (def_v == 1) def_v = 0;
                            }
{command}{def_sets}         { count (); def_sets = 1; }
{command}{def_grammar}      { count (); def_sets = 0; def_x = 0; def_v = 0; }

{non_terminal}              { count ();
                              if (def_v == 1)
                              {
                                symbol* s = (symbol*) gdsl_list_insert_tail (V, (void*) yytext);
                                symbol_set_initial (s);
                              }
                              else
                              {
                                return make_no_terminal (yytext);
                              }
                            }
{terminal}                  { count ();
                              if (def_x == 1)
                              {
                                gdsl_list_insert_tail (X, (void*) yytext);
                              }
                              else
                              {
                                return make_terminal (yytext);
                              }
                            }

.|{spaces}|{comment}        { count (); }
\n                          { line_nb++; col_nb = 1; if (def_sets == 0) return CR; }

%%

extern void*
yy_start_lex (const FILE* file, int size)
{
    YY_BUFFER_STATE nbuf = yy_create_buffer ((FILE*) file, size);
    yy_switch_to_buffer (nbuf);
    return (void*) nbuf;
}

extern void
yy_stop_lex (void* nbuf)
{
    yy_delete_buffer ((YY_BUFFER_STATE) nbuf);
}

extern unsigned long int
yy_get_line_number (void)
{
  return line_nb;
}

extern unsigned long int
yy_get_column_number (void)
{
  return col_nb;
}

/******************************************************************************/

static void count (void)
{
  col_nb++;
}

static int make_no_terminal (char* s)
{
    yy_lval.string = (char*) calloc (sizeof (char), 1 + strlen (s));
    strcpy (yy_lval.string, s);
    return NON_TERMINAL;
}

static int make_terminal (char* s)
{
    yy_lval.string = (char*) calloc (sizeof (char), 1 + strlen (s));
    strcpy (yy_lval.string, s);
    return TERMINAL;
}


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
