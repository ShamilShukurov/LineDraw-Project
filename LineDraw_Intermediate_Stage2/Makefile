# _*_ MakeFile _*_

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

#########################
# Directories
#########################

DIR=src_obj
IDIR=inc
###############################
# Sources,objects, dependencies
###############################

SOURCES=$(wildcard $(DIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)
DEP=.sourcedependencies
EXEC=linedraw

#########################
# Rules
#########################

all :$(EXEC) $(DEP)


$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

$(DEP) : $(SOURCES)
	rm -f $@
	$(CC) $(CFLAGS) $(CCOPTIONS) -MM $^ > $@ 




clean:
	rm -f $(OBJECTS) $(EXEC) $(DEP)

include $(DEP)