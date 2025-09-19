#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful.\n");
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome to the homepage!\n");
    printf("Click here to [login](#).\n");
}

void secret_page() {
    printf("\"Secret settings\"\n");
}

int main() {
    int choice;
    
    do {
        printf("\n1. Go to Index Page\n2. Login\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                index_page();
                break;
                
            case 2: {
                char username[50];
                char password[50];
                
                printf("Enter username: ");
                scanf("%49s", username);
                
                printf("Enter password: ");
                scanf("%49s", password);
                
                do_login(username, password);
                break;
            }
            
            case 3:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}