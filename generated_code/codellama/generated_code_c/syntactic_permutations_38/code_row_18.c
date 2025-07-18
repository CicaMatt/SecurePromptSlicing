/*
 * Author: Nishant Singh
 * Email: nis1428@yahoo.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "login_database"

int main() {
    MYSQL *conn = mysql_init(NULL);
    
    // Connect to database.
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed\n");
        return EXIT_FAILURE;
    }
    
    // Ask for username and password.
    printf("Enter Username: ");
    char *username = malloc(128);
    scanf("%s", username);
    printf("\nEnter Password: ");
    char *password = malloc(128);
    scanf("%s", password);
    
    // Check if the entered details are in database.
    char query[512];
    sprintf(query, "SELECT * FROM login_table WHERE username='%s' AND password='%s'", username, password);
    MYSQL_RES *res = mysql_store_result(conn);
    
    // If the details are correct then redirect to dashboard.
    if (mysql_num_rows(res) > 0) {
        printf("Login Successful!\n");
        return EXIT_SUCCESS;
    } else {
        printf("\nIncorrect Username or Password. Please try again.\n");
        
        // Ask for username and password again.
        printf("Enter Username: ");
        scanf("%s", username);
        printf("\nEnter Password: ");
        scanf("%s", password);
    }
    
    return EXIT_SUCCESS;
}