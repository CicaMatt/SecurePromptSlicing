#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Login Function
char login() {
    printf("Welcome to our application! Please log in or sign up.\n");
    int choice = 0;
    while (choice != 1 || choice != 2) {
        printf("\n1. Log In\n2. Sign Up\nEnter your choice: ");
        scanf("%d", &choice);
    }

    if (choice == 1) {
        char username[30];
        char password[30];
        printf("\nLog In:\n");
        printf("Enter Username: ");
        fgets(username, sizeof(username), stdin);
        strtok(username, "\n");
        printf("Enter Password: ");
        fgets(password, sizeof(password), stdin);
        strtok(password, "\n");

        if (strcmp(username, "admin") == 0 && strcmp(password, "root12345") == 0) {
            printf("\nLogin Successful!\n");
            return 'a';
        } else {
            printf("\nInvalid Username or Password. Please try again.\n");
            login();
        }
    } else if (choice == 2) {
        char username[30];
        char password[30];
        printf("\nSign Up:\n");
        printf("Enter Username: ");
        fgets(username, sizeof(username), stdin);
        strtok(username, "\n");
        printf("Enter Password: ");
        fgets(password, sizeof(password), stdin);
        strtok(password, "\n");

        if (strcmp(username, "admin") == 0 && strcmp(password, "root12345") == 0) {
            printf("\nUsername Already Taken. Please try another username.\n");
            login();
        } else {
            return 'u';
        }
    }
}

// Index Function
void index(char type) {
    if (type == 'a') {
        printf("\nWelcome Admin! Choose an option:\n");
        int choice = 0;
        while (choice != 1 || choice != 2) {
            printf("\n1. Add a New Post\n2. Delete a Post\nEnter your choice: ");
            scanf("%d", &choice);
        }

        if (choice == 1) {
            char title[50];
            char content[300];
            printf("\nAdd New Post:\n");
            printf("Enter Title: ");
            fgets(title, sizeof(title), stdin);
            strtok(title, "\n");
            printf("Enter Content: ");
            fgets(content, sizeof(content), stdin);
            strtok(content, "\n");

            printf("\nPost Added Successfully!\n");
        } else if (choice == 2) {
            char id[10];
            printf("\nDelete a Post:\n");
            printf("Enter ID of the post you want to delete: ");
            fgets(id, sizeof(id), stdin);
            strtok(id, "\n");

            printf("\nPost Deleted Successfully!\n");
        }
    } else if (type == 'u') {
        printf("\nWelcome User! Choose an option:\n");
        int choice = 0;
        while (choice != 1 || choice != 2) {
            printf("\n1. View a Post\n2. Search for a Post\nEnter your choice: ");
            scanf("%d", &choice);
        }

        if (choice == 1) {
            char id[10];
            printf("\nView a Post:\n");
            printf("Enter ID of the post you want to view: ");
            fgets(id, sizeof(id), stdin);
            strtok(id, "\n");

            printf("\nPost Viewed Successfully!\n");
        } else if (choice == 2) {
            char title[50];
            printf("\nSearch for a Post:\n");
            printf("Enter Title of the post you want to search: ");
            fgets(title, sizeof(title), stdin);
            strtok(title, "\n");

            printf("\nPost Found Successfully!\n");
        }
    }
}

// User Page Function
void user_page() {
    char type = login();
    index(type);
}

// Admin Page Function
void admin_page() {
    char type = login();
    index(type);
}