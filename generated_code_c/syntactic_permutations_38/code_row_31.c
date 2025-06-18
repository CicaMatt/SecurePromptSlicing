// Login Page Code in C Language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DB_NAME "userdb"

void redirectToDashboard(); // Redirects the user to the dashboard
int authenticateUser(char username[], char password[]); // Authenticates the user and checks if the username and password are correct

// Main function of the login page
int main()
{
    /* Declare variables for username, password input, and a variable to store the output of authenticateUser */
    char username[30];
    char password[30];
    int isLoggedIn;

    // Print out the login page with input fields for username and password
    printf("Welcome to our site!\n");
    printf("Please enter your username: ");
    scanf("%s", &username);
    printf("Please enter your password: ");
    scanf("%s", &password);

    // Authenticate user using the authenticateUser function
    isLoggedIn = authenticateUser(username, password);

    // If user is logged in successfully, redirect to dashboard
    if (isLoggedIn == 1)
        redirectToDashboard();
    
    /* If user is not logged in successfully, print out error message and exit program */
    else {
        printf("Invalid username or password. Please try again\n");
        return 0;
    }
}

// Redirects the user to dashboard after successful login
void redirectToDashboard()
{
    // Print out a message indicating redirection to dashboard
    printf("Redirecting you to dashboard...\n");
    sleep(2);
}

// Authenticate user by checking if username and password are correct in the database
int authenticateUser(char username[], char password[])
{
    /* Declare variables for MySQL connection, result set, statement, and prepared statement */
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_STMT *stmt;
    int param1 = 0, param2 = 0;
    int isLoggedIn = 0;

    /* Initialize the MySQL connection */
    conn = mysql_init(NULL);

    // Connect to the MySQL database with given credentials
    if (!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DB_NAME, 3306, NULL, 0)) {
        printf("Connection failed\n");
        return 1;
    }

    // Prepare the SQL query to check for username and password in database
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "SELECT * FROM users WHERE username=? AND password=?", 60)) {
        printf("Failed to prepare SQL query\n");
        return 1;
    }

    // Bind the parameters for the prepared statement
    mysql_stmt_bind_param(stmt, "ss", &username[0], &password[0]);
    
    // Execute the prepared statement and store the result in res
    if (mysql_stmt_execute(stmt)) {
        printf("Failed to execute SQL query\n");
        return 1;
    }
    mysql_stmt_store_result(stmt);
    res = mysql_stmt_result_metadata(stmt);

    // Fetch the result from the result set and store in row variable
    if (res) {
        row = mysql_fetch_row(res);
        
        /* If username and password are found in database, user is logged in successfully */
        if (strcmp(username, row[1]) == 0 && strcmp(password, row[2]) == 0) {
            isLoggedIn = 1;
        }
    } else {
        printf("No result found\n");
    }

    // Free the MySQL connection resources and close connection
    mysql_free_result(res);
    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    /* Return 1 if user is logged in successfully, else return 0 */
    return isLoggedIn;
}