##########################################################################
#                                                                        #
#   Module: Makefile                                                     #
#                                                                        #
#   Makefile for the joinc program                                       #
#                                                                        #
#   This file is part of the SeqCode 1.0 distribution                    #
#                                                                        #
#     Copyright (C) 2017 - Enrique BLANCO GARCIA                         #
#                                                                        #
#  This program is free software; you can redistribute it and/or modify  #
#  it under the terms of the GNU General Public License as published by  #
#  the Free Software Foundation; either version 2 of the License, or     #
#  (at your option) any later version.                                   #
#                                                                        #
#  This program is distributed in the hope that it will be useful,       #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#  GNU General Public License for more details.                          #
#                                                                        #
#  You should have received a copy of the GNU General Public License     #
#  along with this program; if not, write to the Free Software           #
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             #
##########################################################################


###########################
# 0. Compilation options  #
###########################

CC= gcc 
OPTS=-I$(INCLUDE) 
LOPS = -lm
INCLUDE= ./include
CDIR= ./src
OBJ = ./objects

###########################
# 1. List of programs     #
###########################

ALL= all
MESS1 = mess1
MESS2 = mess2

JOINC= joinc
BIN_JOINC= bin/$(JOINC)


###########################
# 2. List of objects      #
###########################

OBJ_JOINC= $(OBJ)/account.o $(OBJ)/readargv_joinc.o \
	$(OBJ)/RequestMemory.o $(OBJ)/GetFileSize.o \
	$(OBJ)/ReadGeneset.o $(OBJ)/ProcessFullGeneset.o \
	$(OBJ)/ProcessFullGenesetAverage.o $(OBJ)/ProcessFullGenesetAverageGenes.o \
	$(OBJ)/Dictionary.o $(OBJ)/Output.o \

###########################
# 3. Makefile rules       #
###########################

### GENERAL

$(OBJ)/account.o :  $(CDIR)/account.c
	$(CC) -c $(OPTS) $(CDIR)/account.c -o $(OBJ)/account.o

$(OBJ)/Dictionary.o :  $(CDIR)/Dictionary.c
	$(CC) -c $(OPTS) $(CDIR)/Dictionary.c -o $(OBJ)/Dictionary.o

$(OBJ)/GetFileSize.o: $(CDIR)/GetFileSize.c
	$(CC) -c $(OPTS) $(CDIR)/GetFileSize.c -o $(OBJ)/GetFileSize.o

$(OBJ)/Output.o: $(CDIR)/Output.c
	$(CC) -c $(OPTS) $(CDIR)/Output.c -o $(OBJ)/Output.o

$(OBJ)/RequestMemory.o : $(CDIR)/RequestMemory.c
	$(CC) -c $(OPTS) $(CDIR)/RequestMemory.c -o $(OBJ)/RequestMemory.o

### JOINC

$(BIN_JOINC):  $(OBJ)/$(JOINC).o $(OBJ_JOINC)
	$(CC) $(OPTS) -o $(BIN_JOINC) $(OBJ)/$(JOINC).o $(OBJ_JOINC) $(LOPS)

$(OBJ)/$(JOINC).o : $(CDIR)/$(JOINC).c
	$(CC) -c $(OPTS) $(CDIR)/$(JOINC).c -o $(OBJ)/$(JOINC).o 

$(OBJ)/readargv_joinc.o :  $(CDIR)/readargv_joinc.c
	$(CC) -c $(OPTS) $(CDIR)/readargv_joinc.c -o $(OBJ)/readargv_joinc.o

$(OBJ)/ReadGeneset.o :  $(CDIR)/ReadGeneset.c
	$(CC) -c $(OPTS) $(CDIR)/ReadGeneset.c -o $(OBJ)/ReadGeneset.o

$(OBJ)/ProcessFullGeneset.o: $(CDIR)/ProcessFullGeneset.c
	$(CC) -c $(OPTS) $(CDIR)/ProcessFullGeneset.c -o $(OBJ)/ProcessFullGeneset.o

$(OBJ)/ProcessFullGenesetAverage.o: $(CDIR)/ProcessFullGenesetAverage.c
	$(CC) -c $(OPTS) $(CDIR)/ProcessFullGenesetAverage.c -o $(OBJ)/ProcessFullGenesetAverage.o

$(OBJ)/ProcessFullGenesetAverageGenes.o: $(CDIR)/ProcessFullGenesetAverageGenes.c
	$(CC) -c $(OPTS) $(CDIR)/ProcessFullGenesetAverageGenes.c -o $(OBJ)/ProcessFullGenesetAverageGenes.o


###########################
# 4. Makefile global rules#
###########################

mess1:
	@echo "***** Step 1. Building the joinc program          *****"
mess2:
	@echo "***** [OK] joinc program successfully generated   *****\n"

$(ALL):	$(MESS1) \
	$(BIN_JOINC) \
	$(MESS2) \

clean:
	rm -f $(OBJ)/*.o $(BIN_JOINC) *~ $(INCLUDE)/*~ $(CDIR)/*~
