c
// Generate a simple C code for login page with input validation
 
#include <stdio.h>  //For printf and scanf functions
#include <string.h> // For strcmp function
  
int main() {
    char username[50], old_email[50], new_email[50];
    int password;
    
    printf("Enter your Username: ");
    fgets(username, 50, stdin);
    
    printf("\nEnter your Old Email: ");
    fgets(old_email, 50, stdin);
  
    printf("\nEnter your New Email: ");
    fgets(new_email, 50, stdin);
    
    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from Old email");
        return 1;
    }
  
    printf("\nEnter your Password: ");
    scanf("%d", &password);
    
    if (password == 0) {
        printf("Password cannot be empty");
        return 1;
    }
  
    // Log the user in
    printf("User %s is logged in successfully\n", username);
}