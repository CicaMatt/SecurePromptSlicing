#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> // For usleep if needed
#endif

#include "mysql/mysql.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define HASHED_PASSWORD_LENGTH 64

unsigned long hash_password(const char *password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned long hashed_value = hash_password(password);

    snprintf(hashed_password, HASHED_PASSWORD_LENGTH, "%lx", hashed_value);

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users(username, password) VALUES('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("User successfully registered.\n");

    mysql_close(conn);
    return 0;
}


To compile and run this code:
1. Ensure you have MySQL installed and a database named `test_db` with a table `users(username VARCHAR(50), password CHAR(64))`.
2. Install the MySQL C API library.
3. Compile using: 
   - On Linux: `gcc -o register_user register_user.c $(mysql_config --cflags --libs)`
   - On Windows, link against `libmysql.dll` and include necessary headers.

Make sure to replace database connection parameters as needed for your setup.