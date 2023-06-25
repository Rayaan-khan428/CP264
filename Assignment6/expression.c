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



/* 
 * convert infix expression in string to postfix expression represented by QUEUE and return the postfix expression queue. 
*/
QUEUE infix_to_postfix(char *infixstr) {

    char *p = infixstr;

    STACK stack = {0}; // Stack for infix expression
    QUEUE queue = {0}; // Queue for postfix expression

    int sign = 1, num = 0;

    while (*p) {
        // step 1: check if the character we are looking at is a negative
        if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
            sign = -1;
        }

        // step 2: check if it is an operand
        else if (*p >= '0' && *p <= '9') {
            num = *p - '0';
            while (*(p + 1) >= '0' && *(p + 1) <= '9') {
                num = num * 10 + (*(p + 1) - '0');
                p++;
            }
            enqueue(&queue, new_node(sign * num, 0));
            sign = 1;
        } else if (*p == '(') {
            push(&stack, *p);
        } else if (*p == ')') {
            while (stack.top && stack.top[stack.top - 1] != '(') {
                enqueue(&queue, new_node(pop(&stack), 0));
            }
            if (stack.top && stack.top[stack.top - 1] == '(') {
                pop(&stack); // Discard the opening parenthesis
            }
        } else if (type(*p) == 1) { // in the case it is an operator
            while (stack.top && type(stack.top[stack.top - 1]) == 1 && precedence(*p) <= precedence(stack.data[stack.top - 1])) {
                enqueue(&queue, new_node(pop(&stack), 0));
            }
            push(&stack, *p);
        }
        p++;
    }
    while (stack.top) {
        enqueue(&queue, new_node(pop(&stack), 0));
    }
    return queue;
}


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
    QUEUE postfixQueue = infix_to_postfix(infixstr);
    int result = evaluate_postfix(postfixQueue);
    return result;
}
