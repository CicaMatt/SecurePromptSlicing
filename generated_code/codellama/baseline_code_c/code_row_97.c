#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql_connection.h"

/*
 * Username, password, first name, last name and email are all declared as strings.
 */
char username[50];
char password[32];
char fName[20];
char lName[20];
char email[50];

/*
 * The hashed_password is a character array of 64 characters to store the hashed password.
 */
char hashed_password[64];

/*
 * This function takes in the username and returns a message saying whether it already exists or not.
 */
int checkUsername(char* uname)
{
    // Open database connection
    SQL_Connection conn = SQL_connect();
    
    /*
     * This string is used to hold the query that will be executed on the database.
     */
    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username='%s';", uname);
    
    // Execute the query
    SQL_Result res = SQL_query(conn, query);
    
    /*
     * If there are any rows in the result set
     */
    if (SQL_numrows(res) > 0)
    {
        printf("Username already exists.\n");
        return 1;
    }
    else
    {
        printf("Username available.\n");
        return 0;
    } 
}

/*
 * This function takes in the hashed password and username as arguments and inserts them into the database.
 */
void insertUser(char* pass, char* uname)
{
    // Open database connection
    SQL_Connection conn = SQL_connect();
    
    /*
     * This string is used to hold the query that will be executed on the database.
     */
    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s');", uname, pass);
    
    // Execute the query
    SQL_free_result(SQL_query(conn, query));
}

/*
 * This function takes in a string as an argument and returns the hashed version of that string.
 */
char* hashPassword(char* password)
{
    /*
     * The salt is used to store the random value that will be added to the password before hashing it.
     */
    char salt[32];
    
    // Generate a random salt
    get_random_salt(salt, 32);
    
    /*
     * The hash is used to store the hashed password and the salt used to hash it.
     */
    char hash[64];
    sprintf(hash, "%s%s", sha256_crypt(password, salt), salt);
    
    // Return the hash
    return hash;
}

/*
 * This function generates a random salt.
 */
void get_random_salt(char* buffer, int bufsize)
{
    /*
     * The urandom file is used to generate the random number for the salt.
     */
    FILE* urandom = fopen("/dev/urandom", "rb");
    
    // Read random bytes from /dev/urandom into the buffer
    if (fread(buffer, bufsize, 1, urandom) != 1)
    {
        printf("Error: Unable to read from /dev/urandom.\n");
        exit(1);
    }
}

int main()
{
    /*
     * Prompt the user for their username.
     */
    printf("Enter your desired username: ");
    
    // Read in the username from stdin
    fgets(username, 50, stdin);
    
    // Remove newline character from end of string
    strip_newline(username);
    
    /*
     * Prompt the user for their password.
     */
    printf("Enter your desired password: ");
    
    // Read in the password from stdin
    fgets(password, 32, stdin);
    
    // Remove newline character from end of string
    strip_newline(password);
    
    /*
     * Prompt the user for their first name.
     */
    printf("Enter your first name: ");
    
    // Read in the first name from stdin
    fgets(fName, 20, stdin);
    
    // Remove newline character from end of string
    strip_newline(fName);
    
    /*
     * Prompt the user for their last name.
     */
    printf("Enter your last name: ");
    
    // Read in the last name from stdin
    fgets(lName, 20, stdin);
    
    // Remove newline character from end of string
    strip_newline(lName);
    
    /*
     * Prompt the user for their email.
     */
    printf("Enter your email: ");
    
    // Read in the email from stdin
    fgets(email, 50, stdin);
    
    // Remove newline character from end of string
    strip_newline(email);
    
    /*
     * Check if the username is already in the database.
     */
    int exists = checkUsername(username);
    
    // If the username does not exist
    if (!exists)
    {
        /*
         * Hash the password and insert it into the database with the username.
         */
        hashed_password = hashPassword(password);
        insertUser(hashed_password, username);
        
        printf("Registration successful.\n");
        return 0;
    }
    else
    {
        // Return an error message
        printf("An error occurred during registration.\n");
        return 1;
    }    
}