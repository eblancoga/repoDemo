/*************************************************************************
*                                                                        *
*   Module: ProcessFullGenesetAverage                                    *
*                                                                        *
*   Reading the file with the info for the full set of genes             *
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

extern account *m;

void ResetSum(float* sum)
{
  int i;

  /* Reset each available position */
  for (i=0; i<MAXSUM; i++)
    {
      sum[i]=0;
    }
}
  

long ProcessFullGenesetAverage(char* FileName, dict* GeneNames)
{
  /* File handle */
  FILE* file;
  
  /* Total number of genes and genes found in the file */
  long nFullGenes;
  long nFoundGenes;

  /* Split every input line into two tokens to access the first column */
  char line[MAXLINE];
  char* line1;
  char* line2;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char gene[MAXGENENAME];
  float value;

  /* Code for the hash */
  int key;

  /* Total sum on each position around the TSS */
  float sum[MAXSUM];

  /* Position in the line (excluding gene name) */
  int position;
  
  char mess[MAXSTRING];
  

  /* 0. Open the FullGeneset file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The FullGeneset file can not be opened to read");
  
  /* 1. Reset counters */
  nFullGenes = 0;
  nFoundGenes = 0;  
  ResetSum(sum);
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);
		  
      /* Extracting values of current line: */
      line1 = (char *) strtok(line,SPACE);
      
      /* There is one mandatory column */
      if (line1 == NULL)
	{
	  sprintf(mess,"Unexpected format <gene> in the line %ld:\n-->%s\n",
		  nFullGenes,lineCopy);
	  printMess(mess);
	}

      /* F1: Gene name */
      if (sscanf(line1,"%s",gene) != 1)
	{
	  sprintf(mess,"Wrong format in the gene name:\n-->%s\n",lineCopy);
	  printError(mess);
	}
      
      /* Check if this gene was included into our subset of working genes */
      key = getkeyDict(GeneNames,gene);
      if (key != NOTFOUND)
	{
	  /* Parsing all the values of the current line to calculate the average */
	  /* Split the first value */
	  line2 = (char *) strtok(NULL,SPACE);
	  position = 0;

	  while(line2 != NULL)
	    {
	      /* Extract the value */
	      sscanf(line2,"%f",&value);
	      sum[position] = sum[position] + value;

	      /* Split the next value */
	      line2 = (char *) strtok(NULL,SPACE);
	      
	      position++;
	    }

	  nFoundGenes++;
	}
      
      /* (info) Increase the total number of genes in the file */
      nFullGenes++;
    }
      
  fclose(file);

  /* Print the averaged value per postition around the TSS */
  OutputAverageValues(sum,nFoundGenes);
  
  /* Return the number of found genes in the file */
  return(nFoundGenes);
}
  
