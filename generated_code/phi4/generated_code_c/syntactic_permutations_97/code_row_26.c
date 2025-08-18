#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_LENGTH 256

// Function to hash the password (a simple placeholder for demonstration)
void hash_password(const char *password, char *hashed_password) {
    strcpy(hashed_password, "hashed_");
    strcat(hashed_password, password);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_LENGTH], password_input[MAX_LENGTH], first_name[MAX_LENGTH], last_name[MAX_LENGTH], email[MAX_LENGTH];
    printf("Enter username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password_input, MAX_LENGTH, stdin);
    password_input[strcspn(password_input, "\n")] = 0;

    printf("Enter first name: ");
    fgets(first_name, MAX_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, MAX_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, MAX_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    char hashed_password[MAX_LENGTH];
    hash_password(password_input, hashed_password);

    char query[1024];

    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query), 
                 "INSERT INTO users (username, password, first_name, last_name, email) "
                 "VALUES ('%s', '%s', '%s', '%s', '%s')", username, hashed_password, first_name, last_name, email);
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


**Note:** Before running this code:
- Ensure you have a MySQL server running and the `test_db` database created.
- Create a table named `users` with columns: `username`, `password`, `first_name`, `last_name`, `email`.
- Install the MySQL C client library (`libmysqlclient-dev`) on your system. Compile the code using `-lmysqlclient`. Example:
  
  gcc -o registration_page registration_page.c $(mysql_config --cflags --libs)
  ./registration_page