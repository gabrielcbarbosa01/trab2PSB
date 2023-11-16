CFLAGS = -Wall -O2
PROG = main
FONTES = mymemory.c main.c
OBJETOS = $(FONTES:.c=.o)
LIBRARY = liblibminhalib.a  

$(PROG): $(OBJETOS) $(LIBRARY)
	@gcc $(CFLAGS) $(OBJETOS) -o $@ -L. -llibminhalib -lm

$(LIBRARY): mymemory.o
	@ar rcs $@ $^

clean:
	@rm -f $(OBJETOS) $(PROG) $(LIBRARY)