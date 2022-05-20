/*************************************************************************
*                                                                        *
*   Module: joinc                                                        *
*                                                                        *
*   joinc main program                                                   *
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

/************************************************************************
                            ENVIRONMENTAL variables
************************************************************************/

/* Verbose flag (memory/processing information) */
int VRB=0;

/* Accounting time and results */
account *m;

/* Average TSS profile output */
int AVG=0;

/* Average GENE profile output */
int AVGGENE=0;


/************************************************************************
                             MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char GenesetFile[FILENAMELENGTH],
    FullGenesetFile[FILENAMELENGTH];

  dict* GeneNames;
  long FileSize;

  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_joinc(argc,argv,GenesetFile,FullGenesetFile);
  sprintf(mess,"\n\n\t\t\t***** Running %s (%s) by Enrique Blanco (%d) *****\n\n",
	  JOINC,VERSION,YEAR);
  printRes(mess);
  StartingTime(mess,m);
  printMess(mess);

  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  GeneNames = (dict *) RequestMemoryDictionary();
  
  /* 2. Read the file with the names of the subset of genes */
  printMess("2. Reading the subset of Genes");
  FileSize = GetFileSize(GenesetFile);
  sprintf(mess,"%s: %.2lf Mb",GenesetFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  m->nGenes = ReadGenesetFile (GenesetFile,GeneNames);
  sprintf(mess,"Subset file: Name was successfully acquired for %d genes",m->nGenes);
  printRes(mess);

  /* 3. Process the Full Geneset file */
  printMess("3. Processing the full information file");
  FileSize = GetFileSize(FullGenesetFile);
  sprintf(mess,"%s: %.2lf Mb",FullGenesetFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  if (AVG)
    {
      m->nFoundGenes = ProcessFullGenesetAverage(FullGenesetFile,GeneNames);
      sprintf(mess,"(average) %d genes were successfully found",m->nFoundGenes);
      printRes(mess);
    }
  else
    {
      if (AVGGENE)
	{
	  m->nFoundGenes = ProcessFullGenesetAverageGenes(FullGenesetFile,GeneNames);
	  sprintf(mess,"(average gene) %d genes were successfully found",m->nFoundGenes);
	  printRes(mess);
	}
      else
	{
	  m->nFoundGenes = ProcessFullGeneset(FullGenesetFile,GeneNames);
	  sprintf(mess,"(selection) %d genes were successfully found",m->nFoundGenes);
	  printRes(mess);
	}
    }
  
  /* 4. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
