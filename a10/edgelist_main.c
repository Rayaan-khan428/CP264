/*
-------------------------------------------------------
Project:  cp264oc-a10q1
File:     edgelist_main.c
About:    public test driver
Author:   HBF
Version:  2023-06-21
-------------------------------------------------------
*/
#include <stdio.h>
#include "edgelist.h"

int main(){
  EDGELIST *elg = new_edgelist();  
  add_edge_end(elg, 0, 2, 3);
  add_edge_end(elg, 2, 1, 4);
  add_edge_end(elg, 1, 3, 9);
  add_edge_end(elg, 1, 4, 11);  
  printf("display_edgelist():\n", weight_edgelist(elg));  
  display_edgelist(elg);
  printf("\nweight:%d\n", weight_edgelist(elg));
  clean_edgelist(&elg);
  return 0;
}
