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


%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
    
#include <gdsl.h>

#include "parser.h"
#include "scanner.h"
#include "main.h"
#include "misc.h"
#include "rules.h"

static gdsl_list_t tmp;

extern int yy_lex (void);
extern int yy_error (char*);
extern int yy_wrap (void);

%}

%union
{
    char* string;
}

%token ARROW OR CR EPSILON

%token <string> TERMINAL NON_TERMINAL

%start begin

%%

begin     : /* epsilon */
          | begin rule
          | begin CR                            
          | error CR                               { YYABORT; }
          ;

rule      : NON_TERMINAL ARROW                     {
                                                     char* nt = $1;
                                                     gdsl_element_t e = gdsl_list_search (V, strings_compare, (void*) nt);
						     rule* r = (rule*) gdsl_list_insert_tail (G, e);
						     tmp = rule_get_production (r);
						     free (nt);
                                                   } 
            production CR
          ;

production: EPSILON                                { /* EPSILON IS ALWAYS AT END OF LIST X */
	                                             gdsl_list_insert_tail (tmp, gdsl_list_get_head (X));
                                                   }
          | TERMINAL                               {
                                                     char* t = $1;
                                                     gdsl_element_t e = gdsl_list_search (X, strings_compare, (void*) t);
                                                     gdsl_list_insert_tail (tmp, e);
						     free (t);
	                                           }
          | NON_TERMINAL                           {
                                                     char* nt = $1;
 	                                             gdsl_element_t e = gdsl_list_search (V, strings_compare, (void*) nt);
						     gdsl_list_insert_tail (tmp, e);
						     free (nt);
                                                   } 
          | production EPSILON                     { /* EPSILON IS ALWAYS AT END OF LIST X */
	                                             gdsl_list_insert_tail (tmp, gdsl_list_get_head (X));
	                                           }
          | production TERMINAL                    { 
                                                     char* t = $2;
                                                     gdsl_element_t e = gdsl_list_search (X, strings_compare, (void*) t);
						     gdsl_list_insert_tail (tmp, e);
						     free (t);
						   } 
	  | production NON_TERMINAL                {
                                                     char* nt = $2;
	                                             gdsl_element_t e = gdsl_list_search (V, strings_compare, (void*) nt);
						     gdsl_list_insert_tail (tmp, e);
						     free (nt);
                                                   }
          | production OR EPSILON                  {
                                                     gdsl_element_t e = gdsl_list_search (X, strings_compare, (void*) "|");
						     gdsl_list_insert_tail (tmp, e);
						     /* EPSILON IS ALWAYS AT END OF LIST X */
						     gdsl_list_insert_tail (tmp, gdsl_list_get_head (X));
	                                           }
          | production OR TERMINAL                 { 
	                                             char* t = $3;
	                                             gdsl_element_t e1 = gdsl_list_search (X, strings_compare, (void*) "|");
                                                     gdsl_element_t e2 = gdsl_list_search (X, strings_compare, (void*) t);
						     gdsl_list_insert_tail (tmp, e1);
						     gdsl_list_insert_tail (tmp, e2);
						     free (t);
	                                           }
          | production OR NON_TERMINAL             { 
                                                     char* nt = $3;
	                                             gdsl_element_t e1 = gdsl_list_search (X, strings_compare, (void*) "|");
						     gdsl_element_t e2 = gdsl_list_search (V, strings_compare, (void*) nt);
						     gdsl_list_insert_tail (tmp, e1);
						     gdsl_list_insert_tail (tmp, e2);
						     free (nt);
                                                   }
          ;

%%

extern int
yy_parse_file (const FILE* input_file)
{
    int         rc;
    void*       buf;
    struct stat input_file_stat;
    
    if (fstat (fileno ((FILE*) input_file), &input_file_stat) < 0)
    {
	return -1;
    }
    
    if (input_file_stat.st_size <= 0)
    {
	return -2;
    }
    
    buf = yy_start_lex (input_file, input_file_stat.st_size);
    if (buf == NULL)
    {
	return -3;
    }
    
    rc = yy_parse ();

    yy_stop_lex (buf);

    return rc;
}

extern int yy_error (char* s)
{
    fprintf (stderr, "*** Syntax error in line %ld, column %ld (%s)\n",
	     yy_get_line_number (), yy_get_column_number (), s);
    return 1;
}

extern int yy_wrap (void)
{
    return 1;
}


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
