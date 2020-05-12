//Josue Uriarte Reyes
//Joauriar
//PA4
//-----------------------------------------------------------------------------
// GraphTest.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   
   Graph G =newGraph(25);
   Graph C = newGraph(4);

   addEdge(C, 1, 2);
   printf("added first edge\n");
   addEdge(C, 3, 1);
   printf("added second edge\n");

   printGraph(stdout, C);
   printf("\n");

   for(int i=1; i<25; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=15 ) addEdge(G, i, i+7);
   }

   addEdge(G, 14, 11);
   addEdge(G, 12, 1);
   addEdge(G, 22, 5);
   addEdge(G, 8, 6);

   addArc(G, 3, 1);
   addArc(G, 7, 2);
   addArc(G, 10, 12);
   addArc(G, 18, 22);

   printGraph(stdout, G);

   printf("Order of G: %d\n", getOrder(G));
   printf("Order of C: %d\n\n", getOrder(C));

   printf("Size of G: %d\n", getSize(G));
   printf("Size of C: %d\n\n", getSize(C));

   BFS(G, 6);
   List L = newList();
   getPath(L, G, 5);

   printf("path of 6-5: ");
   printList(stdout, L);
   printf("\n");

   List R = newList();
   BFS(G, 1);
   getPath(R, G, 15);

   printf("path of 1-15: ");
   printList(stdout, R);
   printf("\n");

   List P = newList();
   BFS(G, 10);
   getPath(P, G, 25);

   printf("path of 10-25: ");
   printList(stdout, P);
   printf("\n\n");

   makeNull(G);

   printGraph(stdout, G);

   // Free objects
   freeList(&P);    
   freeList(&R);
   freeList(&L);
   freeGraph(&G);
   freeGraph(&C);


   return(0);
}