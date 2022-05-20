/*************************************************************************
*                                                                        *
*   Module: joinc.h                                                      *
*                                                                        *
*   Definitions, data structures types and imported headers              *
*                                                                        *
*   This file is part of the seqcode 1.0 distribution                    *
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

/* Required libraries */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

/*************************************************************************
A. DEFINITIONS
*************************************************************************/

/* Maximum chars per input line             */
#define MAXLINE 50000             

/* Maximum length for strings (mess)        */
#define MAXSTRING 1000            

/* Maximum length for gene symbol names     */
#define MAXGENENAME 100            

/* Maximum number of distinct genes         */
#define MAXGENES 100000

/* Maximum of positions to analyze          */
#define MAXSUM 8000

/* Length of the sequence for TSS plots     */
#define TSSPLOTSIZE 2000

/* Maximum length of filenames              */
#define FILENAMELENGTH 200       

/* Maximum number of usage messages         */
#define MAXUSAGE 5

/* The name of the games                    */
#define VERSION             "SeqCode_v1.0"  
#define JOINC               "joinc"  

/* Dictionary definitions (hash)            */
#define MAXENTRY 97              
#define MAXTYPE 50               
#define MAXINFO 100
#define NOTFOUND -1

/* Tab space within fields                  */
#define TAB "\t"

/* New line character                       */
#define NL "\n"

/* White space character                    */
#define SPACE " "

/* Equal character                          */
#define sEQ "="

/* Comma between exon coordinates (refgene) */
#define CSV ","

/* Gene with no predefined transcript       */
#define NMNULL "NMNULL"

/* File size constant                       */
#define MEGABYTE 1048576

/* TMP file (BG)                            */
#define TMPFILE "/tmp/fileSeqCode"

/* UCSC headers                             */
#define TRACK "track"

/* Time constants                           */
#define MINUTE 60
#define YEAR 2016

/* Message (info)/X chars for big files     */
#define MESSAGE_FREQ 100000

/* Message (info)/X chars for small files   */
#define MESSAGE_FREQ_SMALL 1000      

/* DNA strands                              */
#define cFORWARD '+'
#define cREVERSE '-'

/* Boolean values                           */
#define TRUE 1
#define FALSE 0

/* Promoter limits for GenomeDistribution   */
#define PROMOTERSIZE 2500
#define PROXIMALPOINT 500

/* Non-defined scores (BED 4th column)      */
#define NOSCORE  0.0
#define sNOSCORE "0.0"

/* Range of values for plotTSS profiles     */
#define MINLENGTH 500
#define MAXLENGTH 5000

/* Maximum gene length                      */
#define MAXGENELENGTH 2500000

/* Million (for normalization)              */
#define MEGA 1000000

/* Input formats                            */
#define BEDGRAPH 0
#define WIG 1
#define SAM 2

/* Macros (functions)                       */
#define MIN(a,b) (a<b)?a:b;
#define MAX(a,b) (a>b)?a:b;


/*************************************************************************
B. DATA TYPES
*************************************************************************/

/* Information system */
typedef struct s_account               
{

  int nGenes;
  int nFullGenes;
  int nFoundGenes;
  long nLines;

  long nMemory;

  time_t tStart, tEnd;
} account;

/* Hash (dictionary) */
typedef struct s_node *pnode;          
typedef struct s_node
{
  char s[MAXSTRING];
  int key;
  pnode next;
} node; 

typedef struct s_dict                  
{
  pnode T[MAXENTRY];
  int nextFree; 
} dict;

/* Transcript information */
typedef struct s_transcript
{
  char chr[MAXSTRING];
  char strand;
  long pos1;
  long pos2;
  char gene[MAXGENENAME];
  char nm[MAXGENENAME];
} transcript; 

/* Peak information */
typedef struct s_peak
{
  char  chr[MAXSTRING];
  long  pos1;
  long  pos2;
  char  score[MAXSTRING];
  int   used;
} peak; 


/*************************************************************************
C. IMPORTED HEADERS
*************************************************************************/

/* Information system */
account* RequestMemoryAccounting();
account* InitAcc();

/* Output functions */
void printError(char *s);
void printMess(char* s);
void printRes(char* s);
void StartingTime(char* mess, account* m);
void GetTime(char* mess, account* m);
void OutputTime(account *m);
void printReadingInit();
void printReadingInfo(long nLines);
void printReadingInfoSmall(long nLines);

void OutputMatch(char* line);
void OutputAverageValues(float* sum, long nFoundGenes);
void OutputAverageGeneValues(float* sum, long nFoundGenes);

/* Hash functions */
void resetDict(dict* d);
int setkeyDict(dict* d, char s[]);
int getkeyDict(dict* d, char s[]);
void showDict(dict* d);

/* Read arguments */
void readargv_joinc(int argc,char* argv[],
		    char GenesetFile[FILENAMELENGTH],
		    char FullGenesetFile[FILENAMELENGTH]);

/* Request memory */
dict* RequestMemoryDictionary();

/* Reading input files */
long GetFileSize(char* File);
int ReadGenesetFile (char *FileName, dict* GeneNames);

long ProcessFullGeneset(char* FileName, dict* GeneNames);
long ProcessFullGenesetAverage(char* FileName, dict* GeneNames);
long ProcessFullGenesetAverageGenes(char* FileName, dict* GeneNames);
