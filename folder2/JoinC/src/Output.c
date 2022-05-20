/*************************************************************************
*                                                                        *
*   Module: Output                                                       *
*                                                                        *
*   Management: generating text results (files, stdout)                  *
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

extern int VRB;

extern account* m;

/* Printing messages (information) */
void printMess(char* s)
{
  if (VRB)
    fprintf (stderr, "> %s\n",s);
}

/* Printing stats and results (information) */
void printRes(char* s)
{
  if (VRB)
    fprintf (stderr, "\t%s\n",s);
}

/* Printing error messages */
void printError(char* s)
{
  fprintf(stderr,"ERROR\n\t%s\n",s);
  OutputTime(m);
  exit(1);
}

/* Init message for reading big files */
void printReadingInit()
{
  if (VRB)
    {
      fprintf(stderr, "\tReading:\n");
    }
}

/* Printing messages: big files */
void printReadingInfo(long nLines)
{
  if (VRB && !(nLines % MESSAGE_FREQ))
    {
      fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\t[%10ld lines]",nLines);
    }
}

/* Printing messages: small files */
void printReadingInfoSmall(long nLines)
{
  if (VRB && !(nLines % MESSAGE_FREQ_SMALL))
    {
      fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\t[%10ld lines]",nLines);
    }
}

/* Display the line of information for a gene found in the working geneset */
void OutputMatch(char* line)
{
  printf("%s",line);
}

/* Display the average per position around the TSS */
void OutputAverageValues(float* sum, long nFoundGenes)
{
  int i;

  for (i=0; i<TSSPLOTSIZE*2; i++)
    {
      printf("%d\t%f\n",i-TSSPLOTSIZE,sum[i]/nFoundGenes);
    }
}

/* Display the average per position along the meta-gene */
void OutputAverageGeneValues(float* sum, long nFoundGenes)
{
  int i;

  for (i=0; i<TSSPLOTSIZE*3; i++)
    {
      printf("%d\t%f\n",i-TSSPLOTSIZE,sum[i]/nFoundGenes);
    }
}

/* Extracting the Computing running time by using accounting information */
void StartingTime(char* mess, account* m)
{
    char* s;

    /* 1. Extract the starting time to display */
    s = ctime(&m->tStart);
    s[strlen(s)-1] = '\0';

    /* 2. Prepare the time for printing in a message */
    sprintf(mess,"0. Running on %s",s);
}

/* Extracting the Computing running time by using accounting information */
void GetTime(char* mess, account* m)
{
    char* s;

    /* 1. Extract the starting time to display */
    s = ctime(&m->tStart);
    s[strlen(s)-1] = '\0';

    /* 2. Prepare the time for printing in a message */
    sprintf(mess,"[%s]",s);
}

/* Computing running time by using accounting information */
void OutputTime(account* m)
{
  time_t tEnd;
  int t;
  float caux;
  char mess[MAXSTRING];


  /* Real time */
  time(&tEnd);

  /* CPU time */
  caux = (float)clock() / (float)CLOCKS_PER_SEC;

  t = (int) tEnd - m->tStart;

  /* Correction */
  if (t < caux)
    t++;

  printRes("__________________________________________________________________________\n");
  
  sprintf(mess,"Memory usage: \t%.2f Megabytes",
	  (float)m->nMemory/MEGABYTE);
  printRes(mess);

  sprintf(mess,"CPU time: \t%.2f secs",caux);
  printRes(mess);
  
  sprintf(mess,"Total time: \t%d secs(%.2f mins)\n\n",
	  t,(float)t/MINUTE);
  printRes(mess);
}

