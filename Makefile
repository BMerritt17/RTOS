#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
else ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

#################################
##### SET FILE NAME TO TEST #####
FILE_TO_TEST = TM4C_spi

#################################


#Path Definitions
PATHU 		= lib/unity/
PATHS 		= rtos/src/
PATHT 		= test/
PATHI 		= rtos/inc/
PATHSYS 	= sys/
PATHSYSCORE = lib/CMSIS/Core/Include/
PATHDRIVINC	= drivers/SPI/inc/
PATHDRIVSRC = drivers/SPI/src/
PATHB 	= build/

#determine our source files
SRCU = $(PATHU)unity.c
SRCDRIV = $(wildcard $(PATHDRIVSRC)$(FILE_TO_TEST).c)
SRCS = $(wildcard $(PATHS)$(FILE_TO_TEST).c)
SRCT = $(wildcard $(PATHT)*$(FILE_TO_TEST).c)
SRCSYS = $(wildcard $(PATHSYS)*.c)
SRC = $(SRCU) $(SRCS) $(SRCT) $(SRCSYS) $(SRCDRIV)

#Files We Are To Work With
OBJDRIV = $(patsubst $(PATHDRIVSRC)%.c,$(PATHB)%.o,$(SRCDRIV))
OBJU = $(patsubst $(PATHU)%.c,$(PATHB)%.o,$(SRCU))
OBJS = $(patsubst $(PATHS)%.c,$(PATHB)%.o,$(SRCS))
OBJT = $(patsubst $(PATHT)%.c,$(PATHB)%.o,$(SRCT))
OBJSYS = $(patsubst $(PATHSYS)%.c,$(PATHB)%.o,$(SRCSYS))
OBJ = $(OBJU) $(OBJS) $(OBJT) $(OBJSYS) $(OBJDRIV)

#Other files we care about
DEP = $(PATHU)unity.h $(PATHU)unity_internals.h
TGT_TEST = $(PATHB)test$(TARGET_EXTENSION)

#Tool Definitions
CC=gcc
CFLAGS_TEST=-I. -I$(PATHU) -I$(PATHI) -I$(PATHS) -I$(PATHSYS) -I$(PATHSYSCORE) -I$(PATHDRIVINC)  -D_TEST_ -g

test: $(PATHB) $(TGT_TEST)
	./$(TGT_TEST)

$(PATHB)%.o:: $(PATHS)%.c $(DEP)
	$(CC) -c $(CFLAGS_TEST) $< -o $@

$(PATHB)%.o:: $(PATHT)%.c $(DEP)
	$(CC) -c $(CFLAGS_TEST) $< -o $@

$(PATHB)%.o:: $(PATHU)%.c $(DEP)
	$(CC) -c $(CFLAGS_TEST) $< -o $@

$(PATHB)%.o:: $(PATHSYS)%.c $(DEP)
	$(CC) -c $(CFLAGS_TEST) $< -o $@

$(PATHB)%.o:: $(PATHDRIVSRC)%.c $(DEP)
	$(CC) -c $(CFLAGS_TEST) $< -o $@

$(TGT_TEST): $(OBJ)
	gcc -o $@ $^

clean:
	$(CLEANUP) $(PATHB)*.o
	$(CLEANUP) $(TGT_TEST)

$(PATHB):
	$(MKDIR) $(PATHB)

all: clean test 

.PHONY: all
.PHONY: clean
.PHONY: test
