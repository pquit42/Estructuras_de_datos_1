#include "vertex.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  TAG_LENGTH 64


int main(){
  Vertex *v1 = NULL, *v2 = NULL, *v3 = NULL;
  FILE *f = NULL;
  int c = 0;
  long *id, n = 0;
  char tag[TAG_LENGTH];
  int *state;

  v1 = vertex_initFromString("id:10 tag:one state:1");
  v2 = vertex_initFromString("id:20 tag:two state:2");

  if(!(f = fopen("Vertex.txt", "r"))){
    return -1;
  }

  vertex_print(f, v1);
  vertex_print(f,v2);
  fprintf(f, "\n");
  rewind(f);

  while((fscanf(f, "[%ld, %s, %d]", id, tag, state)) == 3){
    printf("[%ld, %s, %d]", *id, tag, (Label)(*state));
  }
  printf("\n");

  c = vertex_cmp(v1, v2);

  if(c > 0){
    printf("Vertex 1 is greater than vertex 2.\n");
  } else if(c < 0){
    printf("Vertex 2 is greater than vertex 1.\n");
  } else{
    printf("Vertex 1 and vertex 2 are equal.\n");
  }

  printf("Vertex 2 tag: %s\n", vertex_getTag(v2));

  v3 = (Vertex *)vertex_copy((const void *)v1);

  printf("Vertex 3 tag: %ld\n", vertex_getId(v3)); 
  
  n =+ vertex_print(f, v1);
  n =+ vertex_print(f, v3);

  fseek(f, -n, SEEK_CUR);
  while((fscanf(f, "[%ld, %s, %d]", id, tag, state)) == 3){
    printf("[%ld, %s, %d]", *id, tag, (Label)(*state));
  }

  fprintf(f, "\n");
  printf("\n");

  c = vertex_cmp(v1, v3);

  if(c > 0){
    printf("Vertex 1 is greater than vertex 3.\n");
  } else if(c < 0){
    printf("Vertex 3 is greater than vertex 1.\n");
  } else{
    printf("Vertex 1 and vertex 3 are equal.\n");
  }

  return 0;
}
