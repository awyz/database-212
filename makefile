all : userinterface.o databasefunc.o
	gcc -o proj1 userinterface.o databasefunc.o 

userinterface.o : userinterface.c record.h databasefunc.c
	gcc -ansi -pedantic-errors -Wall -c userinterface.c

databasefunc.o : databasefunc.c record.h
	gcc -ansi -pedantic-errors -Wall -c databasefunc.c

clean :
	rm *.o
	rm dump.txt
