//Josue Uriarte Reyes
//Joauriar
//PA4
//-----------------------------------------------------------------------------
// Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define WHITE 0
#define BLACK 1
#define GRAY 2

/*** Exported type ***/
typedef struct GraphObj{
    List* nbr;
    int* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int src;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
	Graph G = malloc(sizeof(struct GraphObj));
	G->nbr = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->dist = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;
	G->src = NIL;

	//Initializing the array of Lists
	for (int i = 1; i < n+1; i++){
		G->nbr[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->dist[i] = INF;
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
		free(G->dist);

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

//Returning the source of the graph
int getSource(Graph G){
	return G->src;
}

//Return the parent of of u in the graph
int getParent(Graph G, int u){
	return G->parent[u];
}

//Returns the distance from source to u
int getDist(Graph G, int u){
	return G->dist[u];
}

//getPath()
//precondition: getSource(G)!=NIL
//precondition: 1 <= u <= getOrder(G) 
void getPath(List L, Graph G, int u){

	if(getSource(G) == NIL){
		printf("Graph Error: cannot call getPath() on NIL source");
		exit(1);
	}

	if( 1>u || u>getOrder(G)){
		printf("Graph Error: cannot call getPath() with out of bounds index");
		exit(1);
	}

	if(u == G->src){
		append(L, G->src);
	}

	else if(G->parent[u] == NIL){
		append(L, NIL);
	}

	else{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
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

//Changes Graph G back to its empty state
void makeNull(Graph G){

	for(int i = 1; i <= getOrder(G); i++){
		clear((G->nbr[i]));
	}

	G->size = 0;
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

//BFS with s being the source
void BFS(Graph G, int s){

	G->src = s;

	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = WHITE;
		G->dist[i] = INF;
		G->parent[i] = NIL;
	}

	G->color[s] = GRAY;
	G->dist[s] = 0;
	G->parent[s] = NIL;

	List Q = newList();
	append(Q, s);
	moveFront(Q);

	while(index(Q) != -1){

		int x = get(Q);
		//deleteFront(Q);

		List adj = G->nbr[x];
		moveFront(adj);

		while(index(adj) != -1){

			int y = get(adj);

			if(G->color[y] == WHITE){
				G->color[y] = GRAY;
				G->dist[y] = G->dist[x] + 1;
				G->parent[y] = x;
				append(Q, y);
			}
			moveNext(adj);
		}

		G->color[x] = BLACK;
		moveNext(Q);
	}

	freeList(&Q);
}



/*** Other operations ***/
void printGraph(FILE* out, Graph G){

	for(int i = 1; i <= getOrder(G); i++){
		List temp = G->nbr[i];
		moveFront(temp);

		fprintf(out, "%d: ", i);
		printList(out, temp);

		fprintf(out, "\n");
	}

}