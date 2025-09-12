#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing for demonstration; use a secure hash function in production.
    unsigned int i = 0;
    while (i < strlen(password)) {
        hashed_password[i] = password[i] + (i % 3);
        i++;
    }
    hashed_password[i] = '\0';
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    char username[BUFFER_SIZE], password[BUFFER_SIZE], first_name[BUFFER_SIZE],
         last_name[BUFFER_SIZE], email[BUFFER_SIZE];
    char hashed_password[BUFFER_SIZE];

    printf("Enter Username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter First Name: ");
    fgets(first_name, BUFFER_SIZE, stdin);
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter Last Name: ");
    fgets(last_name, BUFFER_SIZE, stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(email, BUFFER_SIZE, stdin);
    email[strcspn(email, "\n")] = '\0';

    hash_password(password, hashed_password);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char query[BUFFER_SIZE];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        printf("Username %s already exists.\n", username);
        mysql_free_result(res);
        mysql_close(conn);
        return EXIT_SUCCESS;
    }
    
    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password, first_name, last_name, email) "
             "VALUES ('%s', '%s', '%s', '%s', '%s')", 
             username, hashed_password, first_name, last_name, email);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration succeeded.\n");
    }
    
    mysql_close(conn);

    return EXIT_SUCCESS;
}


Make sure to:

1. Replace `"root"`, `""` (password), and `"testdb"` with your MySQL username, password, and database name.
2. Ensure the `users` table exists in your database with appropriate columns (`username`, `password`, `first_name`, `last_name`, `email`).