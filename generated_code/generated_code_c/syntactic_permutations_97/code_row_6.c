#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
 
int main()
{
    char username[50], password[50];
    int hashed_password;
    char firstname[50], lastname[50];
    char email[100];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
 
    // Prompt user for input
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", firstname);
    printf("Enter last name: ");
    scanf("%s", lastname);
    printf("Enter email address: ");
    scanf("%s", email);
 
    // Hash password
    hashed_password = hash(password);
 
    // Connect to database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "root", "registration", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    // Check if username already exists in database
    if (mysql_query(conn, "SELECT * FROM users WHERE username = '" + username + "'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    res = mysql_use_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        if (row[0] != NULL) {
            printf("Username already exists.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    // Insert username and hashed password into database
    if (mysql_query(conn, "INSERT INTO users VALUES('" + username + "', '" + hashed_password + "')")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    // Display success message
    printf("Registration successful.\n");
 
    // Close database connection
    mysql_close(conn);
 
    return 0;
}