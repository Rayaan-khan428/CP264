/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"

int get_priority(char op) {
  if (op == '/' || op == '*' || op == '%') 
    return 1;
  else if (op == '+' || op == '-')
    return 0;
  else 
    return -1;    
}


QUEUE infix_to_postfix_symbol(char *infixstr,  HASHTABLE *ht) {
    // your implementation


}

/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"

int get_priority(char op) {
  if (op == '/' || op == '*' || op == '%') 
    return 1;
  else if (op == '+' || op == '-')
    return 0;
  else 
    return -1;    
}


QUEUE infix_to_postfix_symbol(char *infixstr,  HASHTABLE *ht) {
// your implementation
}

int evaluate_infix_symbol(char *infixstr,  HASHTABLE *ht) {
// your implementation
}

int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht) {
    
    // Initialize the stack
    STACK operand_stack;
    operand_stack.height = 0;
    operand_stack.top = NULL;

    // Process the infix expression one character at a time
    for (int j = 0; infixstr[j] != '\0'; j++) {
        char current_char = infixstr[j];

        // If char is a space, skip it
        if (current_char == ' ')
            continue;

        // If char is an operand, push it onto the operand stack
        if (isdigit(current_char)) {
            int operand_value = current_char - '0'; // Convert char to integer
            NODE *operand_node = new_node(operand_value, 0); // Operand type is 0
            push(&operand_stack, operand_node);
        }

        // If char is an operator or ()
        else {
            
            // Lookup the operator or parenthesis in the symbol table (HASHTABLE)
            HSNODE *lookup_node = search(ht, &current_char);
            if (lookup_node == NULL) {
                clean_stack(&operand_stack);
                return -1; // error
            }

            int current_operator_prec = lookup_node->value;

            // Process the operator or parenthesis based on its type
            if (current_operator_prec == 1) {
                
                // If it's an operator, pop two operands from the stack and apply the operator
                NODE *op2_node = pop(&operand_stack);
                NODE *op1_node = pop(&operand_stack);
                if (op1_node == NULL || op2_node == NULL) {
                    clean_stack(&operand_stack);
                    return -1; // error
                }

                int result = 0;
                switch (current_char) {
                    case '+':
                        result = op1_node->data + op2_node->data;
                        break;
                    case '-':
                        result = op1_node->data - op2_node->data;
                        break;
                    case '*':
                        result = op1_node->data * op2_node->data;
                        break;
                    case '/':
                        if (op2_node->data == 0) {
                            clean_stack(&operand_stack);
                            return -1; 
                        }
                        result = op1_node->data / op2_node->data;
                        break;
                    default:
                        clean_stack(&operand_stack);
                        return -1; // error
                }

                // Create a new operand node with the result and push it onto the stack
                NODE *result_node = new_node(result, 0);
                push(&operand_stack, result_node);

                // Clean up memory for the popped operand nodes
                free(op1_node);
                free(op2_node);

            } else if (current_operator_prec == 2) {
                // ignore left parenthesis, since it was already taken care of
                continue;
            } else if (current_operator_prec == 3) {
                // for ')'
                NODE *result_node = pop(&operand_stack);
                if (result_node == NULL || operand_stack.height > 0) {
                    clean_stack(&operand_stack);
                    return -1; // error
                }

                int result = result_node->data;
                free(result_node); // Clean up memory for the result node

                // Return the final result
                return result;
            } else {
                // error in invalid char encountered
                clean_stack(&operand_stack);
                return -1; // error
            }
        }
    }

    NODE *result_node = pop(&operand_stack);
    if (result_node == NULL || operand_stack.height > 0) {
        fprintf(stderr, "Invalid infix expression. Mismatched parentheses or operators.\n");
        clean_stack(&operand_stack);
        return -1; // 
    }

    int result = result_node->data;
    free(result_node); // clean memory

    return result;
}



int evaluate_postfix(QUEUE queue) {
    // your implementation, same as A6Q3


}
