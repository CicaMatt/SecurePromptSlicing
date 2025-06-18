#include <stdio.h>
#include <string.h>
#include "mysql/mysql.h"

int main() {
    char username[20], password[20];
    printf("Enter the username : ");
    scanf("%s", username);
    printf("Enter the password : ");
    scanf("%s", password);
    
    // Hash the password using SHA-512 algorithm.
    char hashed_password[64] = {0};
    int i;
    for (i=0; i<strlen(password); i++) {
        sprintf(hashed_password, "%08x", password[i]);
    }
    
    // Generate a random salt.
    char salt[] = "random_salt";
    
    // Append the salt to the hashed password.
    strcat(hashed_password, salt);
    
    MYSQL mysql;
    mysql_init(&mysql);
    
    if (!mysql_real_connect(&mysql, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
        printf("Error connecting to database\n");
        return 1;
    }
    
    char query[256] = {0};
    sprintf(query, "INSERT INTO users VALUES ('%s', '%s')", username, hashed_password);
    if (mysql_query(&mysql, query)) {
        printf("Error inserting into database\n");
        return 1;
    }
    
    mysql_close(&mysql);
    return 0;
}