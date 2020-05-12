//Josue Uriarte Reyes
//Joauriar
//PA5
//-----------------------------------------------------------------------------
// Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define WHITE 3
#define BLACK 4
#define GRAY 5

int time = 0;

/*** Exported type ***/
typedef struct GraphObj{
    List* nbr;
    int* color;
    int* parent;
    int* disc;
    int* finish;
    int order;
    int size;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
	Graph G = malloc(sizeof(struct GraphObj));

	G->nbr = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->disc = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;

	//Initializing the array of Lists
	for (int i = 1; i < n+1; i++){
		G->nbr[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->disc[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	return G;
}

//Freeing the graph
void freeGraph(Graph* pG){
	
	if(pG!=NULL && *pG!=NULL){

		Graph G = *pG;
		for(int i = 1; i <= getOrder(G); i++){
			freeList(&(G->nbr[i]));
		}

		free(G->nbr);
		free(G->color);
		free(G->parent);
		free(G->disc);
		free(G->finish);

		free(*pG);
		*pG = NULL;
	}

}

/*** Access functions ***/

//Returning the number of verts in a graph
int getOrder(Graph G){
	return G->order;
}

//Returning the number of edges in a graph
int getSize(Graph G){
	return G->size;
}

//Return the parent of of u in the graph
int getParent(Graph G, int u){
	return G->parent[u];
}

int getDiscover(Graph G, int u){
	return G->disc[u];
}

int getFinish(Graph G, int u){
	return G->finish[u];
}


/*** Manipulation procedures ***/

//A private helper that adds the vertex in numerical order
void sortVertex(List L, int v){

	//Nothing in the List so just add the vertex
	if(length(L) == 0){
		append(L, v);
		return;
	}

	//List isnt empty so lets have the cursor in the front
	moveFront(L);

	//As long as index doesnt fall off the end of List
	while(index(L) != -1){

		// if(v == get(L)){
		// 	break;
		// }

		//As soon as the vertex is less than the current value
		//insert the vertex before
		if(v < get(L)){
			insertBefore(L, v);
			break;
		}

		moveNext(L);
	}

	//Reached end of List so just append at the end
	if(index(L) == -1){
		append(L, v);
		return;
	}
	
}

//Adding an edge to the vertexes u and v
void addEdge(Graph G, int u, int v){
	sortVertex(G->nbr[u], v);
	sortVertex(G->nbr[v], u);
	G->size++;
}

//Adding an arc from u to v
void addArc(Graph G, int u, int v){
	sortVertex(G->nbr[u], v);
	G->size++;
}


//DFS-Visit
void Visit(Graph G, List L, int x){
	time++;
	G->disc[x] = time;
	G->color[x] = GRAY;

	List adj = G->nbr[x];
	moveFront(adj);

	while(index(adj) != -1){

		int y = get(adj);

		if(G->color[y] == WHITE){
			G->parent[y] = x;
			Visit(G, L, y);
		}

		moveNext(adj);
	}

	G->color[x] = BLACK;
	time++;
	G->finish[x] = time;
	prepend(L,x);
}


//DFS
void DFS(Graph G, List S){

	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->disc[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	time = 0;

	List S_copy = copyList(S);
	clear(S);

	moveFront(S_copy);
	while(index(S_copy) != -1){

		int x = get(S_copy);

		if(G->color[x] == WHITE){
			Visit(G, S, x);
		}

		moveNext(S_copy);
	}
}


/*** Other operations ***/

Graph transpose(Graph G){
	Graph tG = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++){

		//move the cursor to the front
		moveFront(G->nbr[i]);

		//iterating through the list and adding the arcs to cG
		//but in transpose
		while(index(G->nbr[i]) != -1){
			addArc(tG, get(G->nbr[i]), i);
			moveNext(G->nbr[i]);
		}

	}

	return tG;
}

Graph copyGraph(Graph G){
	Graph cG = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++){

		//move the cursor to the front
		moveFront(G->nbr[i]);

		//iterating through the list and adding the arcs to cG
		while(index(G->nbr[i]) != -1){
			addArc(cG, i, get(G->nbr[i]));
			moveNext(G->nbr[i]);
		}

	}

	return cG;
}

void printGraph(FILE* out, Graph G){

	for(int i = 1; i <= getOrder(G); i++){
		List temp = G->nbr[i];
		moveFront(temp);

		fprintf(out, "%d: ", i);
		printList(out, temp);

		fprintf(out, "\n");
	}

}