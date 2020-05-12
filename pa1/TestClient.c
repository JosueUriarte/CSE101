/****************************************************************************************
*  TestClient.c
*  Test client for List ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    
	printf("working\n");
    
    List A = newList();
	append(A, 1);

	deleteBack(A);

	append(A, 2);


	printf("working\n");

	moveFront(A);

	printf("working\n");



	delete(A);

	printf("working\n");



	append(A, 3);
	append(A, 5);
	moveFront(A);
	insertAfter(A, 12);

	delete(A);
	if (length(A) != 3) return 1;
	printf("working!!!!\n");
	return 0;
	
}