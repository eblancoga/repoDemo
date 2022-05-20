/*************************************************************************
*                                                                        *
*   Module: RequestMemory                                                *
*                                                                        *
*   Asking operating system for memory for data structures               *
*                                                                        *
*   This file is part of the SeqCode 1.0 distribution                    *
*                                                                        *
*     Copyright (C) 2017 - Enrique BLANCO GARCIA                         *
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
*  This program is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*  GNU General Public License for more details.                          *
*                                                                        *
*  You should have received a copy of the GNU General Public License     *
*  along with this program; if not, write to the Free Software           * 
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
*************************************************************************/

#include "joinc.h"

extern account* m;

/* Allocating accounting data structure in memory */
account* RequestMemoryAccounting()
{
  account* m; 

  if ((m = (account *) malloc(sizeof(account))) == NULL)
	printError("Not enough memory: account");

  return(m);
}

/* Allocate the dictionary of gene names */
dict * RequestMemoryDictionary()
{
  dict* d;

  if ((d = (dict *)malloc(sizeof(dict))) == NULL)
    printError("Not enough memory: dictionary of gene names");

  resetDict(d);

  /* Update total memory stats */
  m->nMemory = m->nMemory + sizeof(dict);

  return(d);
}

