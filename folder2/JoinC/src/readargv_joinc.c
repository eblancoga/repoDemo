/*************************************************************************
*                                                                        *
*   Module: readargv_joinc                                               *
*                                                                        *
*   Read set up options and filenames from user input                    *
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

/* Joinc external vars */
extern int VRB;
extern int AVG;
extern int AVGGENE;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_joinc()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-g: Average values around the TSS\n");
  fprintf(stderr,"\t-m: Average values along the meta-gene\n");
  fprintf(stderr,"\t-v: Verbose. Display info messages\n");
  fprintf(stderr,"\t-h: Show this help\n");
  fprintf(stderr,"\n");
}

void readargv_joinc(int argc,char* argv[],
		    char GenesetFile[FILENAMELENGTH],
		    char FullGenesetFile[FILENAMELENGTH])
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\tUser commands\n\nNAME\n\t%s - a program to search information for a subset of genes in a full genome geneset file\n",
	  VERSION,
	  JOINC);
  sprintf(USAGE[1],
	  "SYNOPSIS\n\t%s [-g][-m][-v][-h]\t<GeneSubset.txt> <FullGeneSet.txt>\n",
	  JOINC);
  sprintf(USAGE[2],
         "OUTPUT\n\tOne file with the selection of genes as defined by the user that contains all the full information\n");

  while ((c = getopt(argc,argv,"gmvh")) != -1)
    switch(c)
      {
      case 'g': AVG++;
	break;
      case 'm': AVGGENE++;
	break;
      case 'v': VRB++;
	break;
      case 'h': printHelp_joinc();
	exit(1);
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 2)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Two parameters are expected, %d are provided instead",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the input files  */ 
  strcpy(GenesetFile,argv[optind]); 
  strcpy(FullGenesetFile,argv[optind+1]);

  /* Control on the average options */
  if (AVG && AVGGENE)
    {
      sprintf(mess,"Both average display options are activated (only once permitted)");
      printError(mess);
    }
}
