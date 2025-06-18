// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sha256.h"

// Define username and password variables
char *username;
char *password;
char *hashed_password;

// Define salt variable
char *salt = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Function to generate hashed password
void generate_hashed_password(char *password)
{
    // Generate hashed password using SHA-256 algorithm and salt
    char *hash = sha256_hash(password, strlen(password));
    hashed_password = malloc(strlen(hash) + 1);
    strcpy(hashed_password, hash);
}

// Function to insert username and hashed password into database
void insert_into_database(char *username, char *hashed_password)
{
    // Define MySQL connection variables
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    if (mysql_init(&mysql) == NULL)
    {
        printf("MySQL init failed\n");
        exit(0);
    }

    // Connect to MySQL database
    if (mysql_real_connect(&mysql, "localhost", "root", "password", "dbname", 0, NULL, 0) == NULL)
    {
        printf("MySQL connection failed\n");
        mysql_close(&mysql);
        exit(0);
    }

    // Insert username and hashed password into database
    if (mysql_query(&mysql, "INSERT INTO users VALUES('%s', '%s')", username, hashed_password) != 0)
    {
        printf("MySQL query failed\n");
        mysql_close(&mysql);
        exit(0);
    }

    // Close MySQL connection
    mysql_close(&mysql);
}

// Main function to generate hashed password and insert into database
int main()
{
    // Prompt user for username and password
    printf("Enter username: ");
    scanf("%s", username);
    getchar();
    printf("Enter password: ");
    scanf("%s", password);
    getchar();

    // Generate hashed password using SHA-256 algorithm and salt
    generate_hashed_password(password);

    // Insert username and hashed password into database
    insert_into_database(username, hashed_password);

    return 0;
}