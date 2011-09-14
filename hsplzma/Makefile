# Makefile for MinGW running under cygwin

SRC=Alloc.c LzFind.c LzFindMt.c LzmaDec.c LzmaEnc.c LzmaLib.c Threads.c
SRCPP=hsplzma.cpp
OBJ=$(SRC:.c=.o) $(SRCPP:.cpp=.o)
DLL=hsplzma.dll

CC=i686-pc-mingw32-gcc
OPT=-mwindows -Os

.PHONY: all
all: $(DLL)

%.o: %.c
	$(CC) $(OPT) -o $@ -c $<

%.o: %.cpp
	$(CC) $(OPT) -o $@ -c $<

$(DLL): $(OBJ)
	$(CC) $(OPT) -shared -o $@ $(OBJ) -Wl,--add-stdcall-alias

.PHONY: clean
clean:
	-rm $(OBJ) $(DLL)