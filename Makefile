my-shell:  my-shell.o core_functions.o
	gcc -o my-shell my-shell.o core_functions.o

my-shell.o: my-shell.c
	gcc -c my-shell.c

core_functions: core_functions.c
	gcc -c core_functions.c

clean:
	rm my-shell.o core_functions.o my-shell
