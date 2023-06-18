/*
 * JobID: cp264oc-a4-lab4
 * Name: rayaan khan   
 * ID: 210650310
 */ 
#ifndef DLL_H
#define DLL_H

typedef struct node {
  char data;
  struct node *prev;  
  struct node *next;
} NODE;

typedef struct dllist {
  int length;
  NODE *start;
  NODE *end;
} DLL;

NODE *new_node(char value);
void dll_insert_start(DLL *dllp, NODE *np);
void dll_insert_end(DLL *dllp, NODE *np);
void dll_delete_start(DLL *dllp);
void dll_delete_end(DLL *dllp);
void dll_clean(DLL *dllp);

#endif