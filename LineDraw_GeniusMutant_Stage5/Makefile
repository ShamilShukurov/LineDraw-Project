# _*_MakeFile_*_

#-----------------------------------------
# Sunday February the 2nd 2020
# Arash Habibi
# makefile for quickdraw project
#-----------------------------------------

########################
# OS detection
#########################

OS = $(shell uname)

########################
# Compiler options
#########################

CC=gcc
CFLAGS = -I. -I /usr/include \
				-I /usr/local/include \
				-I /opt/local/include/GL \
 				-I /opt/X11/include	\
				-I inc	\
				-Wno-deprecated


ifeq (${OS},Darwin)
  CFLAGS += -I /System/Library/Frameworks/OpenGL.framework/Headers -I /System/Library/Frameworks/GLUT.framework/Versions/A//Headers
else
  CFLAGS += -I /usr/include/GL -I /usr/include
endif

CCOPTIONS = -g -O0 -Wall

#########################
# Librairies
#########################

ifeq ($(OS),Darwin)
	LIBS = -lm -framework OpenGL -framework GLUT
else
	LIBS = -lm -lGLU -lGL -lglut
endif

#######################################
# Sources, Objects and Includes folders
#######################################
ODIR=obj
SDIR=src
#########################
# Sources and objects
#########################

SOURCES=$(wildcard $(SDIR)/*.c)
OBJECTS=$(SOURCES:$(SDIR)/%.c=$(ODIR)/%.o)
EXEC=linedraw

#########################
# Rules
#########################

all :$(EXEC) $(DEP)


$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CCOPTIONS)

test: $(ODIR)/Vector.o $(ODIR)/LineStrip.o testdir/test.c
	$(CC) $^ -o $@ -Iinc -lm

clean:
	rm -f $(OBJECTS) $(EXEC)
