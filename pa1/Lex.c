//Josue Uriarte
//joauriar
//pa1
//-----------------------------------------------------------------------------
// Lex.c
// Sorts an input file into alphabetical order
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

int main(int argc, char* argv[]){

  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  FILE *in, *out;
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if( in == NULL){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if(out == NULL){
    printf("Unable to open file %s for writing\n",argv[2]);
    exit(1);
  }

  char line[100];
  int lineCount = 0;
  while( fgets(line, 100, in) != NULL){
    lineCount++;
  }
  rewind(in);

  List a = newList();

  char *lines[lineCount];
  for(int i = 0; i < lineCount; i++){
    fgets(line, 100, in);
    lines[i] = (char*)malloc(sizeof(line));
    strcpy(lines[i],line);
  }

  append(a,0);

  //sorting array
  for(int i = 1; i < lineCount; i++){
    moveFront(a);
    int found = 0;
    while (index(a) != -1) { 
      if(strcmp(lines[i],lines[get(a)]) < 0){ 
        insertBefore(a,i); 
        found = 1;
        break;
      }
      moveNext(a); 
    }
    if(found == 0) 
      append(a,i);
  }


  //writing array to the out file
  moveFront(a);
  while(index(a) != -1){
    fprintf(out, "%s",lines[get(a)]);
    moveNext(a);
  }

  //freeing memory
  for(int i = 0; i < lineCount; i++){
    free(lines[i]);
  }
  freeList(&a);

  fclose(in);
  fclose(out);

  return(0);
}
