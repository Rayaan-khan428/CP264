#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

/*
 * auxiliary function 
*/
int get_priority(char op) {
  if (op == '/' || op == '*' || op == '%') 
    return 1;
  else if (op == '+' || op == '-')
    return 0;
  else 
    return -1;    
}

/*
 * auxiliary function 
*/
int type(char c) {
  if (c >= '0' &&  c <= '9' )
     return 0;
  else if (c == '/' || c == '*' || c == '%' || c == '+' || c == '-')
    return 1;
  else if (c == '(')
    return 2;
  else if ( c == ')')
    return 3;  
  else 
    return 4;
}

QUEUE infix_to_postfix(char *infixstr) {
  STACK stack;
  QUEUE postfix_queue;
  stack_init(&stack);
  queue_init(&postfix_queue);

  int i = 0;
  while (infixstr[i] != '\0') {
    char c = infixstr[i];
    int t = type(c);

    if (t == 0) {
      // Operand (digit)
      enqueue(&postfix_queue, c);
    } else if (t == 1) {
      // Operator
      while (!stack_empty(&stack) && get_priority(top(&stack)) >= get_priority(c)) {
        enqueue(&postfix_queue, pop(&stack));
      }
      push(&stack, c);
    } else if (t == 2) {
      // Opening parenthesis
      push(&stack, c);
    } else if (t == 3) {
      // Closing parenthesis
      while (!stack_empty(&stack) && top(&stack) != '(') {
        enqueue(&postfix_queue, pop(&stack));
      }
      if (top(&stack) == '(') {
        pop(&stack);
      } else {
        // Mismatched parentheses error
        fprintf(stderr, "Error: Mismatched parentheses\n");
        exit(1);
      }
    }

    i++;
  }

  while (!stack_empty(&stack)) {
    char top_operator = pop(&stack);
    if (top_operator == '(') {
      // Mismatched parentheses error
      fprintf(stderr, "Error: Mismatched parentheses\n");
      exit(1);
    }
    enqueue(&postfix_queue, top_operator);
  }

  return postfix_queue;
}

/* 
 * convert infix expression in string to postfix expression represented by QUEUE and return the postfix expression queue. 
*/
// QUEUE infix_to_postfix(char *infixstr) {

//     char *p = infixstr;

//     STACK stack = {0}; // Stack for infix expression
//     QUEUE queue = {0}; // Queue for postfix expression

//     int sign = 1, num = 0;

//     while (*p) {
//         // step 1: check if the character we are looking at is a negative
//         if (*p == '-' && (p==infixstr || *(p-1) == '(')) {
//             sign = -1;
//         }

//         // step 2: check if it is an operant
//     }
// }

/* 
 * evaluate and returns the value postfix expression passed by queue.
*/
int evaluate_postfix(QUEUE queue) {
    
    // your implementation
    NODE *p = queue.front; // create a copy of the queue
    STACK stack = {0}; // for evaluating

    int type = 0;
    int result;


    // step 1: check if p is null
    if (p == NULL) {
        return 0;
    }
    

    // iterate through every node in the queue
    while (p) {
        
        type = p->type; // store the type (tells us the opperand)

        if (type == 0) { // if it is an opperand
            push(&stack, new_node(p->data, 0)); // pushing opperand onto the stack, second argument indicates type
        }

        else if (type == 1) { // if it is an operator

            // pop the two numbers at the top of the stack
            int opperand1 = pop(&stack)->data;
            int opperand2 = pop(&stack)->data;
  
            // preform the operation
            switch (p->data) {

                case '+':
                    result = opperand1 + opperand2;
                    break;

                case '-':
                    result = opperand1 - opperand2;
                    break;

                case '*':
                    result = opperand1 * opperand2;
                    break;

                case '/':
                    result = opperand1 / opperand2;
                    break;

                default:
                    break;
                 
            }
            push(&stack, new_node(result, 0));
        }
        p = p->next;
    }
    return result;
}

/* 
 * Evaluate and return the value of infix expression passed by string infixstr, 
 * using infix_to_postfix() and evaluate_postfix() functions.
*/
int evaluate_infix(char *infixstr) {
    // your implementation
    return 1;

}