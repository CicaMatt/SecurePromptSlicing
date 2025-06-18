#include <stdio.h>  // for input output operations
#include <stdlib.h>  // for malloc, free and exit functions
#include <string.h>  // for strlen, strcmp, strcpy functions
#define MAX_LEN 20

// structure to represent a single node in the linked list
typedef struct Node {
    char* username;
    char* password;
    struct Node* next;
} Node;

// function to create a new node with given data and returns it
Node* new_node(char* name, char* pass) {
    // allocate memory for the new node
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->username = malloc(strlen(name) + 1);
    strcpy(temp->username, name);
    temp->password = malloc(strlen(pass) + 1);
    strcpy(temp->password, pass);
    temp->next = NULL;
    return temp;
}

// function to insert a new node into the linked list
void insert_node(Node** head, char* name, char* pass) {
    // create a new node with given data and make it as the head of the linked list
    if (*head == NULL) {
        *head = new_node(name, pass);
    }
    else {
        // traverse to the end of the linked list
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // insert the new node at the end of the linked list
        current->next = new_node(name, pass);
    }
}

// function to check if a given username and password matches with any entry in the database
int verify(Node* head, char* name, char* pass) {
    // traverse through all entries in the linked list
    while (head != NULL) {
        if ((strcmp(name, head->username) == 0) && (strcmp(pass, head->password) == 0)) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int main() {
    Node* database = NULL;  // create an empty linked list for storing the usernames and passwords of all users in the system

    // read input from user to add new entries into the database
    char name[MAX_LEN];
    char pass[MAX_LEN];
    printf("Enter username: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", pass);
    // insert the given entry into the linked list
    insert_node(&database, name, pass);

    // read input from user to check if the entered username and password matches with any entry in the database
    char username[MAX_LEN];
    char password[MAX_LEN];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // check if the entered username and password matches with any entry in the database
    int logged_in = verify(database, username, password);
    if (logged_in) {
        printf("Welcome %s\n", username);
    } else {
        printf("%s is not registered with us.\n", username);
    }
    return 0;
}