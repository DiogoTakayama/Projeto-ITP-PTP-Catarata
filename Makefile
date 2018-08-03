teste : main.c operacoes.o io.o 
	gcc main.c operacoes.o io.o -o programa -lm

operacoes.o : operacoes.c
	gcc -c operacoes.c	-W

io.o : io.c	
	gcc -c io.c -W