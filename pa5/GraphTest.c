//Josue Uriarte Reyes
//Joauriar
//PA5
//-----------------------------------------------------------------------------
// GraphTest.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   
   Graph G =newGraph(20);
   Graph C = newGraph(10);

   addArc(C, 1, 2);
   addArc(C, 2, 4);
   addArc(C, 6, 3);
   addArc(C, 8, 6);
   addArc(C, 2, 9);
   addArc(C, 4, 3);

   printGraph(stdout, C);
   printf("\n");

   for(int i=1; i<20; i++){
      if( i%7!=0 ) addArc(G, i, i+1);
      if( i<=10 ) addArc(G, i, i+7);
   }

   printGraph(stdout, G);

   printf("Order of G: %d\n", getOrder(G));
   printf("Order of C: %d\n\n", getOrder(C));

   printf("Size of G: %d\n", getSize(G));
   printf("Size of C: %d\n\n", getSize(C));

   List L = newList();

   for(int i = 1; i <= getOrder(G); i++){
      append(L, i);
   }

   DFS(G, L);
   printGraph(stdout, G);
   printf("\n");

   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=8; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   printf("\n");

   Graph tG = transpose(G);

   DFS(tG, L);

   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=8; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(tG, i), getFinish(tG, i), getParent(tG, i));
   }
   printf("\n");

   printGraph(stdout, tG);
   printf("\n");
   
   // Free objects
   freeList(&L);
   freeGraph(&G);
   freeGraph(&C);
   freeList(&tG);

   return(0);
}