//Josue Uriarte Reyes
//Joauriar
//PA2
//-----------------------------------------------------------------------------
// List.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

// structs --------------------------------------------------------------------

typedef struct EntryObj{
   int col;
   double val;
} EntryObj;
// private Node type
typedef EntryObj* Entry;
//typedef List* List
typedef struct MatrixObj{
	List *rows;
	int size;
	int nNZE; //Number of Non Zero Entries
}	MatrixObj;

//typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------

Entry newEntry(int col, double val){
	Entry N = malloc(sizeof(EntryObj));
  	N->col = col;
  	N->val = val;
  	return(N);
}

Matrix newMatrix(int n){
	Matrix N = malloc(sizeof(MatrixObj));
	N->rows = calloc(n+1, sizeof(List));
	N->size = n;
	N->nNZE = 0;
	for(int i = 1; i <= n; i++){
		  N->rows[i] = newList();
	}
	return N;
}

void freeMatrix(Matrix* pM){
	if( pM!=NULL && *pM!=NULL ){
      free(*pM);
      *pM = NULL;
   }

}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	return (M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	return (M->nNZE);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){

	if(A->size != B->size){
		return 0;
	}

	if(A->nNZE != B->nNZE){
		return 0;
	}

	for(int i=1; i <= A->size; i++){
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);

		if(index(A->rows[i]) != index(B->rows[i])){
			return 0;
		}

		while(index(A->rows[i]) != -1){
			Entry Ai = get(A->rows[i]);
			Entry Bi = get(A->rows[i]);

			if(Ai->col != Bi->col){
				return 0;
			}

			if(Ai->val != Bi->val){
				return 0;
			}

			moveNext(A->rows[i]);
			moveNext(B->rows[i]);

		}

	}

	return 1;
}

// Manipulation procedures ------------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){

	for(int i=1; i <= M->size; i++){

		moveFront(M->rows[i]);

		while(index(M->rows[i]) != -1){
			Entry Ai = get(M->rows[i]);
			free(Ai);
			moveNext(M->rows[i]);
		}
		clear(M->rows[i]);

	}

	M->nNZE = 0;

}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if( (i > M->size) || (j > M->size) ){
		printf("Matrix Error: calling changeEntry() on invalid index\n");
    	exit(1);
	}

	if( (i < 1) || (j < 1) ){
		printf("Matrix Error: calling changeEntry() with negative col/val\n");
    	exit(1);
	}

	moveFront(M->rows[i]);

	if(index(M->rows[i]) == -1 && x != 0.0){
		Entry Z = newEntry(j,x);
		append(M->rows[i], Z);
		M->nNZE++;
		return;
	}

	while(index(M->rows[i]) != -1){
		Entry E = get(M->rows[i]);

		if(E->col == j && x == 0.0){ //Delete
			delete(M->rows[i]);
			M->nNZE--;
			return;
		}

		if(E->col == j && x != 0.0){ //Replace
			Entry Z = newEntry(j,x);
			insertBefore(M->rows[i],Z);
			delete(M->rows[i]);
			return;
		}

		moveNext(M->rows[i]);
	}

	if(index(M->rows[i]) == -1 && x == 0.0){ //Do Nothing
		return;
	}

	else{		
		Entry Z = newEntry(j,x);	//Insert Before or Append
		moveFront(M->rows[i]);

		while(index(M->rows[i]) != -1){
			Entry E = get(M->rows[i]);

			if(j < E->col ){
				insertBefore(M->rows[i],Z);
				M->nNZE++;
				return;
			}

			moveNext(M->rows[i]);

		}
		
		append(M->rows[i],Z);
		M->nNZE++;

	}

}

Matrix copy(Matrix A){

	Matrix Z = newMatrix(A->size);

	for(int i=1; i <= A->size; i++){

		moveFront(A->rows[i]);

		while(index(A->rows[i]) != -1){
			Entry Ai = get(A->rows[i]);
			changeEntry(Z, i, Ai->col, Ai->val);
			moveNext(A->rows[i]);
		}

	}

	return Z;
}

Matrix transpose(Matrix A){

	Matrix Z = newMatrix(A->size);
	Entry Ai;

	for(int i=1; i <= A->size; i++){

		moveFront(A->rows[i]);

		while(index(A->rows[i]) != -1){
			Ai = get(A->rows[i]);
			changeEntry(Z, Ai->col, i, Ai->val);
			moveNext(A->rows[i]);
		}

	}

	return Z;

}


Matrix scalarMult(double x, Matrix A){

	Matrix Z = newMatrix(A->size);
	int col;
	Entry Ai;

	for(int i=1; i <= A->size; i++){
		moveFront(A->rows[i]);

		while(index(A->rows[i]) != -1){
			Ai = get(A->rows[i]);
			col = Ai->col;
			changeEntry(Z, i, col, (x * Ai->val));
			moveNext(A->rows[i]);
		}

	}

	return Z;
}



Matrix sum(Matrix A, Matrix B){
	return A;
}

Matrix diff(Matrix A, Matrix B){
	return A;
}

Matrix product(Matrix A, Matrix B){
	return A;
}



void printMatrix(FILE* out, Matrix M){

	for(int i=1; i <= M->size; i++){
		moveFront(M->rows[i]);

		if(index(M->rows[i]) != -1){

			fprintf(out, "%d: ", i);
		}

		while(index(M->rows[i]) != -1){
			Entry Ai = get(M->rows[i]);
			fprintf(out, "(");
			fprintf(out, "%d, ", Ai->col);
			fprintf(out, "%.1f) ", Ai->val);
			moveNext(M->rows[i]);

		}

		moveFront(M->rows[i]);
		if(i >= 1 ){
			if(index(M->rows[i]) != -1){
				fprintf(out, "\n");
			}
		}

		
	}

}
