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
    // Initialize the queue to store the postfix expression
    QUEUE postfix_queue;
    postfix_queue.length = 0;
    postfix_queue.front = NULL;
    postfix_queue.rear = NULL;

    // Initialize the stack to handle operators and parentheses
    STACK operator_stack;
    operator_stack.height = 0;
    operator_stack.top = NULL;

    // Process the infix expression character by character
    for (int i = 0; infixstr[i] != '\0'; i++) {
        char current_char = infixstr[i];

        // If the current character is a space, skip it
        if (current_char == ' ')
            continue;

        // If the current character is an operand, enqueue it directly to the postfix queue
        if (isdigit(current_char)) {
            int operand_value = current_char - '0'; // Convert char to integer
            NODE *operand_node = new_node(operand_value, 0); // Operand type is 0
            enqueue(&postfix_queue, operand_node);
        }

        // If the current character is an operator or parenthesis
        else {
            // Lookup the operator or parenthesis in the symbol table (HASHTABLE)
            HSNODE *lookup_node = search(ht, &current_char);
            if (lookup_node == NULL) {
                clean_queue(&postfix_queue);
                return postfix_queue;
            }

            int current_operator_prec = lookup_node->value;

            // Process the operator or parenthesis based on its type
            if (current_operator_prec == 1) {
                // If it's an operator, handle the precedence and enqueue the operators from the stack
                while (operator_stack.height > 0) {
                    NODE *top_operator = pop(&operator_stack);
                    if (top_operator->type != 2) { // Ignore left parenthesis
                        enqueue(&postfix_queue, top_operator);
                    } else {
                        // If a left parenthesis is encountered, break the loop
                        break;
                    }
                }
                NODE *current_operator_node = new_node(current_char, 1); // Operator type is 1
                push(&operator_stack, current_operator_node);
            } else if (current_operator_prec == 2) {
                // If it's a left parenthesis, push it to the operator stack
                NODE *left_parenthesis_node = new_node(current_char, 2); // Left parenthesis type is 2
                push(&operator_stack, left_parenthesis_node);
            } else if (current_operator_prec == 3) {
                // If it's a right parenthesis, enqueue the operators from the stack until a left parenthesis is encountered
                while (operator_stack.height > 0) {
                    NODE *top_operator = pop(&operator_stack);
                    if (top_operator->type != 2) { // Ignore left parenthesis
                        enqueue(&postfix_queue, top_operator);
                    } else {
                        // Pop the left parenthesis and break the loop
                        free(top_operator);
                        break;
                    }
                }
            } else {
                // Invalid operator or parenthesis encountered
                fprintf(stderr, "Invalid operator or parenthesis in the infix expression.\n");
                clean_queue(&postfix_queue);
                return postfix_queue;
            }
        }
    }

    // Enqueue any remaining operators from the stack to the postfix queue
    while (operator_stack.height > 0) {
        NODE *top_operator = pop(&operator_stack);
        if (top_operator->type != 2) { // Ignore left parenthesis
            enqueue(&postfix_queue, top_operator);
        } else {
            clean_queue(&postfix_queue);
            return postfix_queue;
        }
    }

    // Return the postfix queue
    return postfix_queue;


}

int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht) {
    // Initialize the stack to handle operands and intermediate results
    STACK operand_stack;
    operand_stack.height = 0;
    operand_stack.top = NULL;

    // Process the infix expression character by character
    for (int i = 0; infixstr[i] != '\0'; i++) {
        char current_char = infixstr[i];

        // If the current character is a space, skip it
        if (current_char == ' ')
            continue;

        // If the current character is an operand, push it onto the operand stack
        if (isdigit(current_char)) {
            int operand_value = current_char - '0'; // Convert char to integer
            NODE *operand_node = new_node(operand_value, 0); // Operand type is 0
            push(&operand_stack, operand_node);
        }

        // If the current character is an operator or parenthesis
        else {
            // Lookup the operator or parenthesis in the symbol table (HASHTABLE)
            HSNODE *lookup_node = search(ht, &current_char);
            if (lookup_node == NULL) {
                fprintf(stderr, "Invalid operator or parenthesis in the infix expression.\n");
                clean_stack(&operand_stack);
                return -1; // Return -1 to indicate an error in evaluation
            }

            int current_operator_prec = lookup_node->value;

            // Process the operator or parenthesis based on its type
            if (current_operator_prec == 1) {
                // If it's an operator, pop two operands from the stack and apply the operator
                NODE *op2_node = pop(&operand_stack);
                NODE *op1_node = pop(&operand_stack);
                if (op1_node == NULL || op2_node == NULL) {
                    fprintf(stderr, "Invalid infix expression. Missing operands for operator.\n");
                    clean_stack(&operand_stack);
                    return -1; // Return -1 to indicate an error in evaluation
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
                            fprintf(stderr, "Invalid infix expression. Division by zero.\n");
                            clean_stack(&operand_stack);
                            return -1; // Return -1 to indicate an error in evaluation
                        }
                        result = op1_node->data / op2_node->data;
                        break;
                    default:
                        fprintf(stderr, "Invalid operator in the infix expression.\n");
                        clean_stack(&operand_stack);
                        return -1; // Return -1 to indicate an error in evaluation
                }

                // Create a new operand node with the result and push it onto the stack
                NODE *result_node = new_node(result, 0);
                push(&operand_stack, result_node);

                // Clean up memory for the popped operand nodes
                free(op1_node);
                free(op2_node);
            } else if (current_operator_prec == 2) {
                // If it's a left parenthesis, ignore it as we handled precedence during the conversion
                continue;
            } else if (current_operator_prec == 3) {
                // If it's a right parenthesis, there should be only one result left on the stack
                NODE *result_node = pop(&operand_stack);
                if (result_node == NULL || operand_stack.height > 0) {
                    fprintf(stderr, "Invalid infix expression. Mismatched parentheses.\n");
                    clean_stack(&operand_stack);
                    return -1; // Return -1 to indicate an error in evaluation
                }

                int result = result_node->data;
                free(result_node); // Clean up memory for the result node

                // Return the final result
                return result;
            } else {
                // Invalid operator or parenthesis encountered
                fprintf(stderr, "Invalid operator or parenthesis in the infix expression.\n");
                clean_stack(&operand_stack);
                return -1; // Return -1 to indicate an error in evaluation
            }
        }
    }

    // After processing the entire infix expression, there should be only one result left on the stack
    NODE *result_node = pop(&operand_stack);
    if (result_node == NULL || operand_stack.height > 0) {
        fprintf(stderr, "Invalid infix expression. Mismatched parentheses or operators.\n");
        clean_stack(&operand_stack);
        return -1; // Return -1 to indicate an error in evaluation
    }

    int result = result_node->data;
    free(result_node); // Clean up memory for the result node

    // Return the final result
    return result;
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