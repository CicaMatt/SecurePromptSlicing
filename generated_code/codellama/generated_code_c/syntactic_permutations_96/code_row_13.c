#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A simple struct to store the username and hashed password */
struct account {
    char *username;
    char *hashed_password;
};

int main(void) {
    /* Initialize a new struct and take input for the username and password */
    struct account user = { .username = NULL, .hashed_password = NULL };
    printf("Enter your desired username: ");
    scanf("%s", &user.username);
    printf("Enter your desired password: ");
    scanf("%s", &user.hashed_password);
    
    /* Call the hash function to generate a salt and concatenate with the hashed password */
    char *salt = generate_salt();
    user.hashed_password = strcat(generate_hash(user.hashed_password, salt), salt);
    
    /* Store in database */
    save(&user);
    
    return 0;
}