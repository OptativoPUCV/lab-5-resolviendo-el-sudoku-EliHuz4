#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int visto[10];

    for (int i = 0; i < 9; i++) {
        for (int z = 0; z < 10; z++){
          visto[z] = 0;
          }

        for (int j = 0; j < 9; j++) {
            int val = n->sudo[i][j];
            if (val != 0) {
                if (visto[val]) return 0;
                visto[val] = 1;
            }
        }
    }

    for (int j = 0; j < 9; j++) {
        for (int z = 0; z < 10; z++){
          visto[z] = 0;
          }

        for (int i = 0; i < 9; i++) {
            int val = n->sudo[i][j];
            if (val != 0) {
                if (visto[val]) return 0;
                visto[val] = 1;
            }
        }
    }

    for (int k = 0; k < 9; k++) {
        for (int z = 0; z < 10; z++){
          visto[z] = 0;
          }

        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int val = n->sudo[i][j];
            if (val != 0) {
                if (visto[val]) return 0;
                visto[val] = 1;
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
          if (n->sudo[i][j] == 0) {
              for (int k = 1; k <= 9; k++) {
                  Node* new_node = copy(n);
                  new_node->sudo[i][j] = k;
                  if(is_valid(new_node))
                  {
                    pushBack(list, new_node);
                  }
              }
              return list;
          }
      }
    }
    return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont) {
  Stack* stack = createStack();
  push(stack, initial);
  *cont = 0;
  while (top(stack) != NULL) {
    Node* TOP = top(stack);
    pop(stack);
    (*cont)++;
    if (is_final(TOP)) {
      return TOP;
    }
    List* adj = get_adj_nodes(TOP);
    Node* aux = first(adj);
    while (aux != NULL) {
      push(stack, aux);             
      aux = next(adj); 
    }
    free(TOP);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/