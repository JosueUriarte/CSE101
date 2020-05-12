//Josue Uriarte Reyes
//Joauriar
//PA5
//-----------------------------------------------------------------------------
// FindComponents.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"


int main(int argc, char* argv[]){

	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
		exit(1);
	}

	//Reading number of verts
	int size;
	fscanf(in, "%d", &size);
	Graph G = newGraph(size);

	//Inserting verts into the newly created graph
	int vert1;
	int vert2;
	//infinite while loop to add the verts
	while(1){
		fscanf(in, "%d", &vert1);
		fscanf(in, "%d", &vert2);

		//meaning we are finished adding edges to the graph
		if(vert1 == 0 && vert2 == 0){
			break;
		}

		//add the vert connected to the other vert
		addArc(G, vert1, vert2);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	//Make list ready for DFS. Will be list of all verts.
	List L = newList();
	for(int i = 1; i <= size; i++){
		append(L, i);
	}

	//Run DFS
	DFS(G, L);
	//Transpose graph G
	Graph tG = transpose(G);
	//Running DFS with the transpose
	DFS(tG,L);


	//Find number of SCC
	int scc = 0;

	//Any NIL parents means 1 scc
	moveFront(L);
	while(index(L) != -1){
		if(getParent(tG, get(L)) == NIL ){
			scc++;
		}
		moveNext(L);
	}

	fprintf(out, "G contains %d strongly connected components:", scc);

	//Printing the strongly connected components
	List C = newList();
	moveBack(L);

	for(int i = 1; i <= scc; i++){
		fprintf(out, "\nComponent %d: ", i);

		while(1){
			prepend(C, get(L));

			if(getParent(tG, get(L)) == NIL){
				printList(out, C); //At NIL parent so print the curr list
				break;
			}

			movePrev(L);
		}

		movePrev(L); //Move cursor from NIL parent
		clear(C);	 //Clear list to use again
	}

	fclose(in);
	fclose(out);
}