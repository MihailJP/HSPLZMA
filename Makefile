# Makefile for MinGW running under cygwin

DIRS=hsplzma hsplzmax

.PHONY: all clean dist

all:
	for i in $(DIRS);do cd $$i;make;cd ..;done

clean:
	for i in $(DIRS);do cd $$i;make clean;cd ..;done

dist: all
	cd Release;make
