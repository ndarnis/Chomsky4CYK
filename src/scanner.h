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


#ifndef _SCANNER_H_
#define _SCANNER_H_


extern void*
yy_start_lex (const FILE* INPUT_FILE,
	      int INPUT_FILE_SIZE
    );

extern void
yy_stop_lex (void* buf
    );

extern unsigned long int
yy_get_line_number (void);

extern unsigned long int
yy_get_column_number (void);


#endif /* _SCANNER_H_ */


/** EMACS **
 * Local variables:
 * mode: c
 * c-basic-offset: 4
 * End:
 */
