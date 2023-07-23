/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *p) {
  BIGINT bn = {0};
  if (p == NULL) 
    return bn;
  else if (!(*p >= '0' && *p <= '9')) {// not begin with digits 
    return bn;
  }
  else if (*p == '0' && *(p+1) == '\0') {// just "0"
    dll_insert_end(&bn, new_node(*p -'0'));
    return bn;
  }  
  else { 
    while (*p) {
      if (*p >= '0' && *p <= '9' ){
        dll_insert_end(&bn, new_node(*p -'0'));
      } else {
        dll_clean(&bn);
        break;
      }
      p++;
    }
    return bn;
  }
}

BIGINT add(BIGINT op1, BIGINT op2) {
    BIGINT result;
    dll_init(&result); // Initialize the result DLL

    NODE *node1 = op1.start; // operand 1
    NODE *node2 = op2.start; // operand 2
    int carry = 0; // Carry value for addition

    while (node1 != NULL || node2 != NULL || carry != 0) {
        int sum = carry;

        if (node1 != NULL) {
            sum += node1->data;
            node1 = node1->next;
        }

        if (node2 != NULL) {
            sum += node2->data;
            node2 = node2->next;
        }

        int digit = sum % 10; // Calculate the digit for the result
        carry = sum / 10; // Calculate the carry value

        dll_insert_end(&result, new_node(digit)); // Insert the digit at the end of the result
    }

    return result;
}

BIGINT Fibonacci(int n) {
    BIGINT fib1 = bigint("0"); // First Fibonacci number (0)
    BIGINT fib2 = bigint("1"); // Second Fibonacci number (1)
    BIGINT fibn = bigint("0"); // Resulting Fibonacci number
    
    if (n == 0)
        return fib1;
    else if (n == 1)
        return fib2;

    for (int i = 2; i <= n; i++) {
        fibn = add(fib1, fib2); // Calculate the next Fibonacci number by adding the previous two
        fib1 = fib2;
        fib2 = fibn;
    }

    return fibn;
}
