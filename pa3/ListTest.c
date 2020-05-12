//Josue Uriarte Reyes
//Joauriar
//PA3
//-----------------------------------------------------------------------------
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
	List A = newList();
	List B = newList();
	List C;

	C = copy(B);

	append(A, 1);
	append(A, 2);
	append(A, 3);
	append(A, 4);

	prepend(B, 1);
	prepend(B, 2);
	prepend(B, 3);
	prepend(B, 4);

	moveFront(A);
	moveBack(B);

	set(A, 10);
	set(B, 10);

	printf("A: ");

	for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%ld ", get(A));
    }

    printf("\n");
    printf("B: ");

    for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%ld ", get(B));
    }

    printf("\n");
    printf("C: ");

    for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%ld ", get(C));
    }

	freeList(&A);
    freeList(&B);
    freeList(&C);

}