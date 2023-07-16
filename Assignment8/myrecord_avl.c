/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue_stack.h"
#include "avl.h"
#include "myrecord_avl.h"

void merge_tree(TNODE **rootp1, TNODE **rootp2) {
    // use recursive or iterative algorithm to traverse tree rootp2, 
    // get record data of each node and insert into rootp1

    if (*rootp2 == NULL) {
        return;
    }

    merge_tree(rootp1, &(*rootp2)->left);
    merge_tree(rootp1, &(*rootp2)->right);
    insert_avl(rootp1, (*rootp2)->data.name, (*rootp2)->data.score);


}

void merge_data(TREE *t1, TREE *t2) {
    // call the merge_tree function to merge t2->root into t1->root
    // update the simple stats of the merged data set using the stats of t1 and t2. 

    merge_tree(&t1->root, &t2->root);
    t1->count += t2->count;
    t1->mean = (t1->mean * (t1->count - t2->count) + t2->mean * t2->count) / t1->count;
    t1->stddev = sqrt(pow(t1->stddev, 2) * (t1->count - t2->count) + pow(t2->stddev, 2) * t2->count + pow(t1->mean - t2->mean, 2) * t1->count * t2->count / pow(t1->count + t2->count, 2));
    t1->mean = mean(t1->root);

}

void add_data(TREE *tree, char *name, float score) {
    // copy from A7
}

void remove_data(TREE *tree, char *name) {
    // copy from A7 
}

// helper
float avl_mean(TREE *root) {
    if (root == NULL) {
        return 0.0;
    }

    float sum = 0.0;
    int count = 0;

    // Traverse the tree in-order and accumulate the sum
    avl_mean_helper(root, &sum, &count);

    if (count > 0) {
        return sum / count;
    } else {
        return 0.0;
    }
}

void avl_mean_helper(TNODE *node, float *sum, int *count) {
    if (node == NULL) {
        return;
    }

    // Traverse left subtree
    avl_mean_helper(node->left, sum, count);

    // Accumulate the score
    *sum += node->data.score;
    *count += 1;

    // Traverse right subtree
    avl_mean_helper(node->right, sum, count);
}