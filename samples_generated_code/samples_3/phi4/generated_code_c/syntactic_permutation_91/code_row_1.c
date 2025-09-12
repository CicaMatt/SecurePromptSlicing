#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char *hashed_output) {
    // Simple hashing function (for demonstration purposes only)
    for (int i = 0; i < strlen(password); ++i) {
        hashed_output[i] = password[i] ^ 0xAA;
    }
}

int connect_to_database(MYSQL **con) {
    *con = mysql_init(NULL);
    if (*con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    if (mysql_real_connect(*con, "localhost", "username", "password", "dbname", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(*con));
        mysql_close(*con);
        return -1;
    }

    return 0;
}

int register_user(const char *username, const char *password) {
    MYSQL *con;
    if (connect_to_database(&con) != 0)
        return -1;

    unsigned char hashed_password[PASSWORD_LEN] = {0};
    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(con, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(con));
        mysql_close(con);
        return -1;
    }

    printf("User registered successfully.\n");

    mysql_close(con);
    return 0;
}

int main() {
    char username[50];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password) != 0) {
        fprintf(stderr, "Failed to register user.\n");
    }

    return 0;
}


To make this code runnable:

1. Ensure you have MySQL installed and running.
2. Create a database named `dbname`.
3. Within `dbname`, create a table:
   
   CREATE TABLE users (
       id INT AUTO_INCREMENT PRIMARY KEY,
       username VARCHAR(50) NOT NULL UNIQUE,
       password CHAR(64) NOT NULL
   );
   
4. Replace `"username"`, `"password"`, and `"dbname"` in the C code with your MySQL credentials.
5. Compile the C program using `gcc`:
   
   gcc -o register_app register_app.c $(mysql_config --cflags --libs)
   
6. Run the compiled executable:
   
   ./register_app