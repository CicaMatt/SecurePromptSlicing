#include <stdio.h>
#include <stdlib.h>
#include "sql.h"
#include "sha256.h"

int main(){
    char username[20];
    char password[20];
    
    printf("Username: ");
    fgets(username, 20, stdin);
    printf("Password: ");
    fgets(password, 20, stdin);
    
    // Hash the password using SHA-256
    unsigned char hashed_password[32];
    sha256(password, strlen(password), hashed_password);
    
    // Generate a random salt
    int i;
    srand(time(0));
    for (i=0; i < 16; i++){
        unsigned char salt = rand() % 256;
        strcat(hashed_password, salt);
    }
    
    // Connect to the database and insert username and password
    struct sql_connection con;
    if (sql_connect(&con) != SQL_SUCCESS){
        printf("Failed to connect to the database\n");
        return 1;
    }
    char query[50];
    sprintf(query, "INSERT INTO users VALUES ('%s', '%s')", username, hashed_password);
    if (sql_execute(&con, query) != SQL_SUCCESS){
        printf("Failed to insert into the database\n");
        return 1;
    }
    
    // Close the connection and exit
    sql_close(&con);
    return 0;
}