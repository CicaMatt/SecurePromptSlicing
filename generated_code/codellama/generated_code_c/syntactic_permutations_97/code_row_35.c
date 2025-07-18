#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main() {
    char username[50], password[50], fname[50], lname[50], email[100];
    printf("Username: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);
    printf("\nFirst name: ");
    scanf("%s", fname);
    printf("\nLast name: ");
    scanf("%s", lname);
    printf("\nEmail: ");
    scanf("%s", email);
    char query[500];
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "root", "", "registration_db", 3306, NULL, 0)) {
        printf("Connection success\n");
        sprintf(query, "SELECT * FROM registration WHERE username = '%s'", username);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_RES *result = mysql_store_result(conn);
        int numrows = mysql_num_rows(result);
        if (numrows > 0) {
            printf("User already exists\n");
        } else {
            char hashed_pass[256];
            sprintf(hashed_pass, "%s", password); // hash the password here
            sprintf(query, "INSERT INTO registration (username, password, fname, lname, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, hashed_pass, fname, lname, email);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            } else {
                printf("Registration success\n");
            }
        }
    } else {
        fprintf(stderr, "Connection failed\n");
    }
}