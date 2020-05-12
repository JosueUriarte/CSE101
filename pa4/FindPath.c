//Josue Uriarte Reyes
//Joauriar
//PA4
//-----------------------------------------------------------------------------
// FindPath.c
// Adds verts to a graph and then prints the distance and shortest
// path from the source to the destination vertex
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

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

	//Read number of verts in a graph
	int size;
	fscanf(in, "%d", &size);

	Graph G = newGraph(size);

	int vert1;
	int vert2;

	// int a; 
	//scanf("This is the value %d", &a); 
	//printf("Input value read : a = %d", a); 

	//While we arent at the EOF(End of file)
	//will eventaully use the double zeroes to break
	while(fgetc(in) != EOF){
		fscanf(in, "%d", &vert1);
		fscanf(in, "%d", &vert2);

		//meaning we are finished adding edges to the graph
		if(vert1 == 0 && vert2 == 0){
			break;
		}

		//add the vert connected to the other vert
		addEdge(G, vert1, vert2);
	}

	//Print the graph to the out file
	printGraph(out, G);
	fprintf(out, "\n");

	int src;
	int dest;

	//Same loop except this time working with destination
	//and path
	while(fgetc(in) != EOF){
		fscanf(in, "%d", &src);
		fscanf(in, "%d", &dest);

		//meaning we are finished with finding the dest
		//and the shortest path
		if(src == 0 && dest == 0){
			break;
		}
		

		//Make the tree of the source
		BFS(G,src);

		//Put the path of dest into the list created
		List L = newList();
		getPath(L,G,dest);

		//Printing the distance and shortest path
		if(getDist(G,dest) != INF){
			fprintf(out, "The distance from %d to %d is %d\n", src, dest, length(L)-1);
			fprintf(out, "A shortest %d-%d path is: ", src, dest);
			printList(out, L);
			fprintf(out, "\n\n");
		}

		else{
			fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
			fprintf(out, "No %d-%d path exists\n\n", src, dest);
		}

		//Free list so it can be used again
		freeList(&L);
	}

	freeGraph(&G);
	fclose(in);
	fclose(out);
	return 0;

}