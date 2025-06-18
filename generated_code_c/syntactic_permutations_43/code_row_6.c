// Header files required to run this code
#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    // Create a new node
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    // Initialize the left and right child pointers of this node to NULL
    node->left = NULL;
    node->right = NULL;

    // Store data in this node
    node->data = data;

    return node;
}

// Function to insert a new node at the correct position in the BST
struct Node* insert(struct Node* root, int data) {
    // If the root is NULL, create a new node and return it as the root
    if (root == NULL) {
        return newNode(data);
    }
    else if (data < root->data) {
        // If the data to be inserted is less than the data in this node,
        // insert the data at the left subtree of this node
        root->left = insert(root->left, data);
    }
    else {
        // If the data to be inserted is greater than or equal to the data in this node,
        // insert the data at the right subtree of this node
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to perform in-order traversal of the BST
void inOrder(struct Node* root) {
    // If the current node is NULL, return immediately
    if (root == NULL) {
        return;
    }

    // Perform in-order traversal on the left subtree of this node
    inOrder(root->left);

    // Print the data in this node
    printf("%d ", root->data);

    // Perform in-order traversal on the right subtree of this node
    inOrder(root->right);
}

// Function to perform pre-order traversal of the BST
void preOrder(struct Node* root) {
    // If the current node is NULL, return immediately
    if (root == NULL) {
        return;
    }

    // Print the data in this node
    printf("%d ", root->data);

    // Perform pre-order traversal on the left subtree of this node
    preOrder(root->left);

    // Perform pre-order traversal on the right subtree of this node
    preOrder(root->right);
}

// Function to perform post-order traversal of the BST
void postOrder(struct Node* root) {
    // If the current node is NULL, return immediately
    if (root == NULL) {
        return;
    }

    // Perform post-order traversal on the left subtree of this node
    postOrder(root->left);

    // Perform post-order traversal on the right subtree of this node
    postOrder(root->right);

    // Print the data in this node
    printf("%d ", root->data);
}

// Main function to test above functions
int main() {
    struct Node* root = NULL;

    // Insert values 10, 20, and 30 in the BST
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    printf("In-order traversal: ");
    inOrder(root);

    printf("\nPre-order traversal: ");
    preOrder(root);

    printf("\nPost-order traversal: ");
    postOrder(root);

    return 0;
}