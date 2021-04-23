IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = header.h parts.h relations.h sets.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o listDefinition.o listManipulation.o readFiles.o listSearch.o parts/partsManipulation.o parts/partsSearch.o parts/partsShow.o relations/relManipulation.o relations/relSearch.o relations/relShow.o sets/setsManipulation.o sets/setsSearch.o sets/setsShow.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

start.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
