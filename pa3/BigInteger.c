//Josue Uriarte Reyes
//Joauriar
//PA3
//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
	List longList;
	int sign;
} BigIntegerObj;

typedef struct BigIntegerObj* BigInteger;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
	BigInteger B = malloc(sizeof(BigIntegerObj));
	B->longList = newList();
	B->sign = 0;
	return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
   if(pN!=NULL && *pN!=NULL) { 
      free(*pN);
      *pN = NULL;
   }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: cannot call sign() on NULL BigInteger\n");
    	exit(1);
	}
	return(N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: cannot call compare() on NULL BigInteger\n");
    	exit(1);
	}

	if(sign(A) > sign(B)){
		return 1;
	}

	if(length(A->longList) > length(B->longList)){
		return 1;
	}

	if(sign(A) < sign(B)){
		return -1;
	}

	if(length(A->longList) < length(B->longList)){
		return -1;
	}

	moveFront(A->longList);
	moveFront(B->longList);

	
	return 0;

}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	return 0;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: cannot call makeZero() on NULL BigInteger\n");
    	exit(1);
	}
	clear(N->longList);
	N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){

	if(N->sign == 1){
		N->sign = -1;
	}

	else if(N->sign == -1){
		N->sign = 1;
	}

}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){

	BigInteger A = newBigInteger();
	long mult = 1;
	long val = 0;
	int strlen = 0;
	bool aSign = false;

	//Set the sign to a neg or pos using ASCII value

	if(s[0] == 45){
		A->sign = -1;
		aSign = true;
	}
	else{
		A->sign = 1;

		if(s[0] == 43){
			aSign = true;
		}
	}


	for(strlen = 0; s[strlen] != '\0'; strlen++); //Getting the length of
												  //the string 

	if(aSign == true){
		for(int i = 1; i < strlen; i++){
			val += (s[(strlen) - i] - '0')*mult;
			mult *= 10;

			if(i%9 == 0 || strlen - i == 1){	//When there are nine digits
				append(A->longList, val);		//or at index 1
				mult = 1;						//(before the + or -)
				val = 0;
			}

		}
	}

	else{
		for(int i = 1; i <= strlen; i++){
			val += (s[(strlen) - i] - '0')*mult;
			mult *= 10;

			if(i%9 == 0 || strlen - i == 0){	//9 digits
				append(A->longList, val);		//at index 0
				mult = 1;						//(No + or -)
				val = 0;
			}

		}
	}

	return A;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){

	BigInteger A = newBigInteger();

	moveFront(N->longList);
	while(index(N->longList) != -1){
		append(A->longList, get(N->longList));
		moveNext(N->longList);
	}

	if(sign(N) == 1){
		A->sign = 1;
	}

	if(sign(N) == -1){
		A->sign = -1;
	}

	return A;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){

}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){

	BigInteger C = newBigInteger();

	if(sign(A) != sign(B)){

	}

	moveFront(A->longList);
	moveFront(B->longList);


	return C;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){

}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
	return A;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	return A;
}

// Other operations -----------------------------------------------------------

BigInteger normalize(BigInteger N){
	long carry = 0;

	moveFront(N->longList); //Moving to the front to check MSB

	//Checking if MSB is less than 0 to multiply each value by -1
	if(get(N->longList) < 0){

		N->sign = -1; //Change the sign to negative
		while(index(N->longList) != -1){ //Multiplying everything by -1
			long val = get(N->longList);
			set(N->longList, val*-1);
			moveNext(N->longList);
		}

	}

	moveBack(N->longList); //Move to LSB

	while(index(N->longList) != -1){
		set(N->longList, get(N->longList)+carry);

		if(get(N->longList) < 0){
			set(N->longList, get(N->longList)+9);
			carry = -1;
		}

		else{
			carry = get(N->longList)/9;
			set(N->longList, get(N->longList)%9);
		}

		movePrev(N->longList); //movePrev since going from the back
	}

	return N;

}

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){

	moveBack(N->longList);

	while(index(N->longList) != -1){
		fprintf(out, "%ld", get(N->longList));
		movePrev(N->longList);
	}

}

