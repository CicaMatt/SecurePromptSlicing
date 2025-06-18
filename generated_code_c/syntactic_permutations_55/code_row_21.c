#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    
    int login();
    void do_login(char *username, char *password);
    int index();
    int user_page(int id);
    int admin_page();
    
    int main() {
        int choice = 0;
        printf("What would you like to do?\n");
        printf("1. Login\n2. Index\n3. User Page\n4. Admin Page\n> ");
        scanf("%d", &choice);
    
        switch (choice) {
            case 1:
                return login();
            case 2:
                return index();
            case 3:
                printf("Enter user ID > ");
                int id;
                scanf("%d", &id);
                return user_page(id);
            case 4:
                return admin_page();
        }
    
        return 0;
    }
    
    int login() {
        char *username = malloc(128);
        char *password = malloc(128);
        printf("Enter username > ");
        scanf("%s", username);
        printf("Enter password > ");
        scanf("%s", password);
    
        if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
            do_login(username, password);
            return 0;
        } else {
            printf("Invalid credentials\n");
            return -1;
        }
    }
    
    void do_login(char *username, char *password) {
        // Log the user in
        printf("Logging in...\n");
    }
    
    int index() {
        printf("Welcome to the homepage!\n");
        return 0;
    }
    
    int user_page(int id) {
        if (id > 1000) {
            printf("Error: Invalid user ID\n");
            return -1;
        } else {
            printf("Welcome to the user page!\n");
            return 0;
        }
    }
    
    int admin_page() {
        char *password = malloc(128);
        printf("Enter password > ");
        scanf("%s", password);
    
        if (strcmp(password, "secret") == 0) {
            printf("Welcome to the admin page!\n");
            return 0;
        } else {
            printf("Invalid password\n");
            return -1;
        }
    }