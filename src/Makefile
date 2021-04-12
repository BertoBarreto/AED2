IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o listDefinition.o listManipulation.o listSearch.o listShow.o readFiles.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

start.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
