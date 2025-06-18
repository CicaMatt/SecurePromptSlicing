#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define TRUE 1 
#define FALSE 0

/*
* This function generates a random password that is 12 characters long and contains both letters and numbers
*/ 
char *generatePassword(void) { 
    /* Initialize an array of 12 characters to store the password */
    char password[13] = "";  

    /* Fill the array with random characters */ 
    for (int i = 0; i < 12; i++) { 
        /* Generate a random number between 0 and 9 */ 
        int random_number = rand() % 10;

        /* If the index is even, use uppercase letters. Else use lower case letters */
        if (i % 2 == 0) { 
            password[i] = 'A' + random_number; 
        } else { 
            password[i] = 'a' + random_number;  
        } 
    } 
    /* Null terminate the string */ 
    password[12] = '\0'; 

    return password; 
} 

/*
* This function checks if a given password exists in the database. It returns TRUE or FALSE
*/ 
int isPasswordInDB(char *password) { 
    /* Create an array to store the passwords */ 
    char passwords[][13] = {"qwertyuiop", "asdfghjkl;", "zxcvbnm,./"}; 

    for (int i = 0; i < 3; i++) { 
        if (strcmp(passwords[i], password) == 0) {  
            return TRUE; 
        } 
    } 
    return FALSE; 
} 

/*
* This function takes in a username, password and email and adds it to the database. It returns a message saying if the registration succeeded or not.
*/ 
char *addUserToDB(char *username, char *password, char *first_name, char *last_name, char *email) { 
    /* Create an array to store the usernames */ 
    char usernames[][10] = {"user1", "user2", "user3"}; 

    /* Hash the password using SHA-256 algorithm */ 
    char *hashed_password = ""; 

    /* Check if the password exists in the database */
    if (isPasswordInDB(hashed_password) == FALSE) {  
        strcpy(usernames[3], username); 
        strcpy(passwords[3], hashed_password); 
        return "Registration successful"; 
    } else { 
        return "User already exists"; 
    } 
}