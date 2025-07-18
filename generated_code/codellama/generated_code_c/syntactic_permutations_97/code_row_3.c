#include <stdio.h> 
#include "stdlib.h" 
#include "string.h" 

int main() {
    /* create variables for username, password, first name, last name and email */
    char *username;
    char *password;
    char *firstname;
    char *lastname;
    char *email;
    
    /* prompt user to enter username, password, first name, last name and email */
    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);
    printf("Enter First Name: ");
    scanf("%s", &firstname);
    printf("Enter Last Name: ");
    scanf("%s", &lastname);
    printf("Enter Email: ");
    scanf("%s", &email);
    
    /* declare a variable to store the result of the query */
    char *result;
    
    /* execute query to check if username already exists in database */
    const char *query = "SELECT username FROM users WHERE username = ?";
    
    /* prepare the statement for execution */
    sqlite3_stmt *stmt; 
    int rc = sqlite3_prepare(db, query, -1, &stmt, NULL);
    
    /* bind values to the parameters of the statement */
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    
    /* execute the statement and store result in variable "result" */
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        result = (char *) sqlite3_column_text(stmt, 0);
    }
    
    /* if username exists in database return message saying username already exists */
    if(result != NULL){
        printf("Username already exists\n");
        
        /* free the memory allocated to the variables */
        free(username);
        free(password);
        free(firstname);
        free(lastname);
        free(email);
    
    /* else if username does not exist in database hash password and insert new user into database */
    } else {
        
        /* hash password */
        char *hashed_password = hash(password); 
        
        /* declare a variable to store the result of the query */
        const char *query2 = "INSERT INTO users (username, password) VALUES(?, ?)";
        
        /* prepare the statement for execution */
        sqlite3_stmt *stmt2; 
        int rc2 = sqlite3_prepare(db, query2, -1, &stmt2, NULL);
        
        /* bind values to the parameters of the statement */
        sqlite3_bind_text(stmt2, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt2, 2, hashed_password, -1, SQLITE_TRANSIENT);
        
        /* execute the statement and store result in variable "result" */
        while((rc2 = sqlite3_step(stmt2)) == SQLITE_ROW) {
            result = (char *) sqlite3_column_text(stmt2, 0);
        }
        
        /* free the memory allocated to the variables */
        free(username);
        free(password);
        free(firstname);
        free(lastname);
        free(email);
    
    /* return message saying registration succeeded */
    printf("Registration successful\n");
        
    }
}