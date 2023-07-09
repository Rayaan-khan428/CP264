/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


TNODE *search(TNODE *root, char *name) {
    TNODE *current = root; // Start from the root of the tree

    while (current) { // Traverse the tree until a suitable node is found or the end of the tree is reached
        if (strcmp(current->data.name, name) < 0) // If the current node's name is less than the target name
            current = current->right; // Move to the right child
        else if (strcmp(current->data.name, name) > 0) // If the current node's name is greater than the target name
            current = current->left; // Move to the left child
        else
            return current; // Return the current node as it matches the target name
    }
    return NULL; // Return NULL if the target name is not found in the tree
}

void insert(TNODE **rootp, char *name, float score) {
    TNODE *node = new_node(name, score); // Create a new node with the given name and score

    if (!*rootp) { // If the root pointer is empty, i.e., the tree is empty
        *rootp = node; // Set the root pointer to the new node
        return; // Exit the function
    }

    TNODE *current = *rootp; // Start from the root of the tree

    while (current) { // Traverse the tree until a suitable position is found
        if (strcmp(name, current->data.name) < 0) { // If the name is less than the current node's name
            if (!current->left) { // If the current node's left child is empty
                current->left = node; // Set the left child to the new node
                return; // Exit the function
            }
            current = current->left; // Move to the left child
        } else if (strcmp(name, current->data.name) > 0) { // If the name is greater than the current node's name
            if (!current->right) { // If the current node's right child is empty
                current->right = node; // Set the right child to the new node
                return; // Exit the function
            }
            current = current->right; // Move to the right child
        } else { // If the names are equal
            current->data.score = score; // Update the score of the current node
            return; // Exit the function
        }
    }
}

void delete(TNODE **rootp, char *name) {
    if (!*rootp)
        return; // If the root pointer is empty, there is no tree to delete from, so return.

    TNODE *parent = NULL, *current = *rootp; // Initialize variables for parent and current nodes.
    
    while (current) { // Traverse the tree until a suitable node is found or the end of the tree is reached.
        
        if (strcmp(current->data.name, name) < 0) { // If the current node's name is less than the target name.
            parent = current; // Update the parent node to the current node.
            current = current->right; // Move to the right child.
            continue;
        }
        else if (strcmp(current->data.name, name) > 0) { // If the current node's name is greater than the target name.
            parent = current; // Update the parent node to the current node.
            current = current->left; // Move to the left child.
            continue;
        }
        
        // Found a node that matches the target name.
        
        // Situation one: Children not found.
        if (!(current->left || current->right)) { // If the current node has no left or right child.
            if (!parent)
                *rootp = NULL; // If the current node is the root node, set the root pointer to NULL.
            else {
                if (parent->left == current)
                    parent->left = NULL; // If the current node is the left child of its parent, set the parent's left child to NULL.
                else
                    parent->right = NULL; // If the current node is the right child of its parent, set the parent's right child to NULL.
            }
            free(current); // Free the memory of the current node.
        }
        
        // Situation two: Only one child found.
        else if ((!current->left) != (!current->right)) { // If the current node has exactly one child.
            TNODE *child = (current->left) ? current->left : current->right; // Determine the child node.
            if (!parent)
                *rootp = child; // If the current node is the root node, set the root pointer to the child node.
            else {
                if (parent->left == current)
                    parent->left = child; // If the current node is the left child of its parent, set the parent's left child to the child node.
                else
                    parent->right = child; // If the current node is the right child of its parent, set the parent's right child to the child node.
            }
            free(current); // Free the memory of the current node.
        }
        
        // Situation three: Two children exist.
        else {
            // Update the minimum value in the right subtree as a replacement for the current node.
            TNODE *succ_parent = current, *succ = current->right; // Initialize variables for the successor parent and successor nodes.
            while (succ->left) { // Find the minimum value in the right subtree (the leftmost node).
                succ_parent = succ; // Update the successor parent node.
                succ = succ->left; // Move to the left child.
            }
            current->data = succ->data; // Replace the data of the current node with the data of the successor node.
            if (succ_parent == current)
                current->right = succ->right; // If the successor parent is the current node, set the current node's right child to the successor's right child.
            else
                succ_parent->left = succ->right; // If the successor parent is not the current node, set the successor parent's left child to the successor's right child.
            free(succ); // Free the memory of the successor node.
        }
    }
}


TNODE *new_node(char *name, float score) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE)); // Allocate memory for a new node

    if (np) { // If memory allocation was successful
        strcpy(np->data.name, name); // Copy the given name into the new node's data structure
        np->data.score = score; // Assign the given score to the new node's data structure
        np->left = NULL; // Set the left child pointer of the new node to NULL
        np->right = NULL; // Set the right child pointer of the new node to NULL
    }

    return np; // Return the pointer to the new node
}


TNODE *extract_smallest_node(TNODE **rootp) {
    TNODE *p = *rootp;
    TNODE *parent = NULL;

    while (p && p->left) {
        parent = p;
        p = p->left;
    }

    if (p) {
        if (parent)
            parent->left = p->right;
        else
            *rootp = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_tree(TNODE **rootp) {

  TNODE *root = *rootp;
  if (root) {
    if (root->left)
      clean_tree(&root->left);
    if (root->right)
      clean_tree(&root->right);
    free(root);
  }
  *rootp = NULL;

}