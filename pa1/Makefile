#Josue Uriarte
#joauriar
#pa1
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

TestClient: TestClient.o List.o
	gcc -o TestClient TestClient.o List.o

TestClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall TestClient.c

submit:
	submit cse101-pt.f19 pa1 List.h List.c ListClient.c Lex.c Makefile README
	
check:
	ls  /afs/cats.ucsc.edu/class/cse101-pt.f19/pa1/joauriar

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o TestClient TestClient.o