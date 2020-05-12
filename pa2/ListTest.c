//Josue Uriarte Reyes
//Joauriar
//PA2
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
    int X[] = {0,1,2,3,4,5,6,7,8,9,10};

    append(A, &X[0]);
    append(A, &X[1]);
    append(A, &X[2]);
    append(A, &X[3]);

    prepend(B, &X[4]);
    prepend(B, &X[5]);
    prepend(B, &X[6]);

    for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
    }

    printf("\n");

    for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
    }

    printf("\n");


    freeList(&A);
    freeList(&B);

}