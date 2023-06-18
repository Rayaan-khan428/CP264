/*--------------------------------------------------
Project: cp264oc-a5q3
File:    bigint_main.c
Author:  HBF
Version: 2023-06-06
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"
#include "bigint.h"

void display_bigint(BIGINT bignumber) {
  NODE *ptr = bignumber.start;
  while ( ptr != NULL) {
    printf("%d", ptr->data);
    ptr = ptr->next;
  }
}


int main(int argc, char* args[]) {
  int n = 100;
  char *opr1 = "1111111111111111111";
  char *opr2 = "8888888888888888889";
  
  if (argc > 1 ) n = atoi(args[1]); 
  if (argc > 2) opr1 = args[2];
  if (argc > 3) opr2 = args[3];
  
  //testing add()
  BIGINT a = bigint(opr1);
  BIGINT b = bigint(opr2); 
  BIGINT s = add(a, b); 
  display_bigint(a);
  printf("%c", '+');
  display_bigint(b);
  printf("=");
  display_bigint(s);
  dll_clean(&a);
  dll_clean(&b);
  dll_clean(&s);

  //testing Fibonacci()
  printf("\nFibonacci(%d)=", n);
  s = Fibonacci(n);
  display_bigint(s);
  printf("\ndigit count:%d", s.length);
  dll_clean(&s);
  return 0;
}
