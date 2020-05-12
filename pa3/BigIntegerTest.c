//Josue Uriarte Reyes
//Joauriar
//PA3
//-----------------------------------------------------------------------------
//  BigIntegerTest.c 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
#include"List.h"

int main(){

	BigInteger A = newBigInteger();
	printf("The sign of A: %d\n", sign(A));

	BigInteger B = stringToBigInteger("+3251");
	printf("The sign of B: %d\n", sign(B));

	BigInteger C = stringToBigInteger("-3251");
	printf("The sign of C: %d\n", sign(C));

	printf("Comparing B and C: %d\n", compare(B,C));
	printf("Comparing C and B: %d\n", compare(C,B));

	negate(B);
	printf("The sign of B after negating: %d\n", sign(B));

	printBigInteger(stdout, stringToBigInteger("123400"));
	printf("\n");

	printBigInteger(stdout, stringToBigInteger("+123400"));
	printf("\n");

}
