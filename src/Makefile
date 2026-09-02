# This file is part of the Chomsky4CYK project [C4CYK].
# Copyright (C) 1998-2026 Nicolas Darnis <ndarnis@free.fr>.
#
# C4CYK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# C4CYK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with C4CYK. If not, see <http://www.gnu.org/licenses/>. 
#
####################################################################
# Project: Chomsky4CYK: Puts a grammar in normal Chomsky form and
#          uses CYK algorithm to check language words.
EXE			= chomsky
AUTHOR_NAME		= "Nicolas DARNIS"
AUTHOR_EMAIL		= ndarnis@free.fr
AUTHOR_WWW		= http://www.numb.fr/
MAJOR			= 1
MINOR			= 1
SYSTEM			= GNU/Linux
####################################################################

# Commands:
CC     		= gcc
LD		= gcc
LEX    		= flex
YACC   		= bison
RM		= rm -f 

# Flags:
CFLAGS 		= -g -O0 -Wall -Wextra -Wstrict-prototypes -pedantic
LFLAGS		= -lm -lgdsl

# Misc:
PREFIX		= yy_
LEX_OUTPUT	= scanner.c
YACC_OUTPUT	= parser.tab.c

# Sources files:
SRCS		= $(YACC_OUTPUT) $(LEX_OUTPUT) misc.c rules.c symbols.c objects.c main.c

# Objects files:
OBJS		= $(SRCS:.c=.o)

####################################################################

all:		$(OBJS)
		$(LD) $(OBJS) -o chomsky $(LFLAGS)

$(YACC_OUTPUT):	parser.y
		$(YACC) -p $(PREFIX) -d -b parser $<

$(LEX_OUTPUT): 	scanner.l
		$(LEX) -o$@ -P$(PREFIX) $<

clean:
		$(RM) core $(EXE) *.~ *~ parser.tab.* scanner.c $(OBJS)

