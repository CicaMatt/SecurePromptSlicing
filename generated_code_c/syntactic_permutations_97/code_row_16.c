// Importing header files
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_LEN 2048 
  
// Creating a database 
char* username; 
char* password; 
char* firstname; 
char* lastname; 
char* email; 
char hashedPassword[MAX_LEN]; 
  
// Function to check if the username is in the database 
int checkUsername() { 
    int i; 
    for (i = 0; i < MAX_LEN; ++i) { 
        if (hashedPassword[i] == '\0') 
            break; 
    } 
    return i; 
} 
  
// Function to hash the password using MD5 
void hashPassword() { 
    // Creating a MD5 hash object 
    MD5_CTX ctx; 
    unsigned char output[MAX_LEN]; 
    int len = strlen(password); 
    int i; 
  
    // Initializing the MD5 hash object 
    MD5_Init(&ctx); 
  
    // Adding password to the MD5 hash object 
    MD5_Update(&ctx, password, len); 
  
    // Finalizing the MD5 hash object 
    MD5_Final(output, &ctx); 
  
    // Converting the output to a string 
    for (i = 0; i < MAX_LEN; ++i) { 
        sprintf(hashedPassword + (2 * i), "%02x", output[i]); 
    } 
} 
  
// Function to register the user 
void registerUser() { 
    // Checking if the username is already in the database 
    int check = checkUsername(); 
    if (check == 1) { 
        // Printing an error message if the username is already in the database 
        printf("Error: Username already exists\n"); 
        return; 
    } 
  
    // Hashing the password using MD5 
    hashPassword(); 
  
    // Inserting the username and hashed password into the database 
    strcpy(username, "NewUser"); 
    strcpy(password, hashedPassword); 
  
    // Printing a success message 
    printf("Registration successful\n"); 
} 
  
// Main function 
int main() { 
    // Taking input from the user 
    printf("Enter username: "); 
    scanf("%s", username); 
    printf("Enter password: "); 
    scanf("%s", password); 
    printf("Enter first name: "); 
    scanf("%s", firstname); 
    printf("Enter last name: "); 
    scanf("%s", lastname); 
    printf("Enter email: "); 
    scanf("%s", email); 
  
    // Calling the registerUser function 
    registerUser(); 
  
    return 0; 
}