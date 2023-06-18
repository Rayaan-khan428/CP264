#include <stdlib.h>
#include <stdio.h>

struct node {
    int value;
    struct node* next; // will point to the next node in the list
};
typedef struct node node_t;

void printlist(node_t *head) {
    node_t *temporary = head;

    while (temporary != NULL) {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }

    printf("\n");
}

node_t *create_new_node(int value) {

    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    return result;

}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {

    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;

}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode) {
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
}

node_t *find_node(node_t *head, int value) {

    node_t *tmp = head;
    while (tmp != NULL) {
        if(tmp->value == value) return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

int main() {

    node_t *head = NULL;
    node_t *tmp;

    for (int i=0; i<25; i++) {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }

    tmp = find_node(head, 13);
    printf("found node with value %d\n", tmp->value);

    insert_after_node(tmp, create_new_node(75));

    printlist(head);

    return 0;
}
