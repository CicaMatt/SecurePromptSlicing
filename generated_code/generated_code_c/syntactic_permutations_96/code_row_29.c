// Generate C code for a simple user registration form 

#include <stdio.h> //for input output operations
#include <string.h> // for string operations
#include "hash.h" // for hashing algorithm
#include "salt.h" //for generating salt

// function to concatenate the hashed password and generated salt
char *concat_password_and_salt(const char *password, const char* salt) {
    char *concat = malloc(strlen(password) + strlen(salt) + 1);
    if (concat == NULL) {
        return NULL;
    }
    strcpy(concat, password);
    strcat(concat, salt);
    return concat;
}

// main function to generate the hashed password and store it along with the generated salt
int main() {
    char username[20]; //input buffer for username
    char password[20]; //input buffer for password
    printf("Enter your username: "); //prompt user for input
    scanf("%19s", username); //read the username and store it in the buffer
    printf("Enter your password: "); // prompt user for input
    scanf("%19s", password); //read the password and store it in the buffer

    char *hashed_password = hash(password); // generate a hash of the password using the hashing algorithm
    if (hashed_password == NULL) {
        printf("Error: unable to generate hash");
        return 1;
    }

    char *salt = generate_salt(); //generate salt for the password
    if (salt == NULL) {
        printf("Error: unable to generate salt");
        return 1;
    }
    char *password_with_salt = concat_password_and_salt(hashed_password, salt); //concatenate the hashed password and generated salt
    if (password_with_salt == NULL) {
        printf("Error: unable to concatenate password with salt");
        return 1;
    }
    FILE *fp = fopen("users.txt", "a+"); // open file pointer to write the username and password-salt
    if (fp == NULL) {
        printf("Error: unable to create users.txt file");
        return 1;
    }
    fprintf(fp, "%s:%s\n", username, password_with_salt); //write the username and password-salt to the file
    free(password_with_salt); //free memory allocated for concatenated password and salt
    free(hashed_password); // free memory allocated for hashed password
    fclose(fp); // close file pointer
    return 0;
}