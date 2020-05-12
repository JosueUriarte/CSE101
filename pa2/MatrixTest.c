//Josue Uriarte Reyes
//Joauriar
//PA2
//-----------------------------------------------------------------------------
//  MatrixTest.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"
     
int main(){

	Matrix A = newMatrix(10);

	// changeEntry(A, 1, 1, 4);
	// changeEntry(A, 1, 2, 2);
	// changeEntry(A, 1, 3, 0);
	// changeEntry(A, 2, 1, 2);
	// changeEntry(A, 3, 1, 0);
	// changeEntry(A, 2, 2, 2);
	// changeEntry(A, 3, 3, 0);
	// makeZero(A);
	// if (NNZ(A) != 0) printf("fail!");
	// printf("pass");

	Matrix A = newMatrix(10);
	Matrix B = newMatrix(10);
	Matrix C = newMatrix(10);
	Matrix D = newMatrix(10);
	Matrix H;

	printf("%d\n", size(A));
	printf("%d\n", size(B));
	printf("%d\n", size(C));

	// changeEntry(C, 1,1,1);
	// changeEntry(D, 2,2,2);

	changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
	changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
	changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
	changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
	changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
	changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
	changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
	changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
	changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

	printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

	printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

	B = transpose(B);
	printf("%d\n", NNZ(B));
	printMatrix(stdout, B);
	printf("\n");

	// H = sum(A, B);
 	// printf("%d\n", NNZ(H));
 	// printMatrix(stdout, H);
 	// printf("\n");

	C = scalarMult(1.5, A);
	printf("%d\n", NNZ(C));
	printMatrix(stdout, C);
	printf("\n");

	printf("%d\n", NNZ(D));
	printMatrix(stdout, D);
	printf("\n");

	printf("%s\n", equals(A, B)?"true":"false" );
	printf("%s\n", equals(C, D)?"true":"false" );
}