#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct node {
        int data;
        struct node *next;
    };
    
    void insert_at_beginning(struct node **ptr_to_head, int new_data) {
        // Allocate memory for the new node
        struct node *new_node = (struct node *) malloc(sizeof(struct node));
    
        if (!new_node) {
            printf("Unable to allocate memory for a new node.\n");
            return;
        }
    
        // Put in the data
        new_node->data = new_data;
    
        // Make next of new node as head and previous as NULL
        new_node->next = (*ptr_to_head);
    
        // Move the head to point to the new node
        *ptr_to_head = new_node;
    }
    
    void print(struct node *head) {
        while (head != NULL) {
            printf("%d ", head->data);
            head = head->next;
        }
        printf("\n");
    }
    
    int main() {
        struct node *head = NULL;
    
        insert_at_beginning(&head, 10);
        insert_at_beginning(&head, 20);
        insert_at_beginning(&head, 30);
    
        print(head);
    
        return 0;
    }