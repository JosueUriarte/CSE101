///Josue Uriarte Reyes
//Joauriar
//PA2
//-----------------------------------------------------------------------------
// List.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   void* data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;
// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


//Constructors-Deconstructors ------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: cannot call length on empty List\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
   if(L==NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->index);
}

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(Q)
void* front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

void* back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
void* get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling get() on empty list\n");
      exit(1);
   }
   if(L->index < 0){
      printf("List Error: calling get() on undefined cursor\n");
      exit(1);
   }
   return(L->cursor->data);
}


// Manipulation procedures ----------------------------------------------------

void clear(List L){
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){

   if(L->length > 0){
      L->cursor = L->front;
      L->index = 0;
   }

}

void moveBack(List L){

   if(L->length > 0){
      L->cursor = L->back;
      L->index = (L->length - 1);
   }

}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
   if(L->cursor != NULL && L->index != 0){
      L->cursor = L->cursor->prev;
      L->index--;
   }
   else if(L->cursor != NULL && L->index == 0){
      L->cursor = NULL;
      L->index = -1;
   }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
   if(L->cursor != NULL && L->index != L->length - 1){
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if(L->cursor != NULL && L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
   }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L,void* data){
   Node N = newNode(data);

   if(L->length == 0){
      L->front = N;
      L->back = N;
   }

   else{
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
      L->index++;
   }
   L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L,void* data){
   Node N = newNode(data);

   if(L->length == 0){
      L->front = N;
      L->back = N;
   }

   else{
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L,void* data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }

   Node N = newNode(data);
   N->next = L->cursor;

   if(L->cursor->prev != NULL){
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
   }
   L->cursor->prev = N;

   if(N->prev == NULL){
      L->front = N;
   }

   L->index++;
   L->length++;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L,void* data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }

   if(L->cursor == L->back){
      append(L,data);
   }
   else{
      Node N = newNode(data);
      N->prev = L->cursor;
      N->next = L->cursor->next;
      L->cursor->next->prev = N;
      L->cursor->next = N;
      L->length++;
   }

}

// Delete the front element. 
// Pre: length()>0
void deleteFront(List L){

   if(L->length == 0){
      printf("List Error: calling deleteFront() on empty list\n");
      exit(1);
   }

   

   if(L->cursor == L->front){
      L->cursor = NULL;
      L->index = -1;
   }

   Node N = L->front;
   L->front = L->front->next;
   freeNode(&N);
   L->length--;
   if(L->index > 0){
      L->index--;
   }
   
}

// Delete the back element. 
// Pre: length()>0
void deleteBack(List L){
   if(L->length == 0){
      printf("List Error: calling deleteBack() on empty list\n");
      exit(1);
   }

   if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }

   Node N = L->back;

   if(L->length > 1){
      L->back = L->back->prev;
   }
   else{
      L->front = NULL;
      L->back  = NULL;
   }

   freeNode(&N);
   L->length--;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){

   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   
   if(index(L) >= 0){

      if(length(L) == 1){
         L->front = NULL;
         L->back = NULL;
         L->length--;
      }

      else{
         if(L->cursor == L->front){
            deleteFront(L);
         }
         else if(L->cursor == L->back){
            deleteBack(L);
         }
         else{
            Node Pre = L->cursor->prev;
            Node Nex = L->cursor->next;
            Pre->next = Nex;
            Nex->prev = Pre;
            L->length--;
         }
      }

      Node N = L->cursor;
      L->cursor = NULL;
      freeNode(&N);
      L->index = -1;


   }

}
