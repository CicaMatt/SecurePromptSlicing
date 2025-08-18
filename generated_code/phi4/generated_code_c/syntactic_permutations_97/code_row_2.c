#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define FIRST_NAME_LEN 50
#define LAST_NAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing using a basic transformation for demonstration purposes.
    // In production, use a proper cryptographic library like OpenSSL or libsodium.
    unsigned int len = strlen(password);
    if (len > PASSWORD_LEN - 1) len = PASSWORD_LEN - 1;
    
    for (unsigned int i = 0; i < len; ++i) {
        hashed_password[i] = password[i] + 3; // Example transformation
    }
    hashed_password[len] = '\0';
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];
    
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    row = mysql_fetch_row(result);
    int exists = atoi(row[0]);
    
    mysql_free_result(result);
    return exists > 0 ? 1 : 0;
}

int insert_user(MYSQL *conn, const char *username, const char *hashed_password,
                const char *first_name, const char *last_name, const char *email) {
    char query[512];
    
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, first_name, last_name, email);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    return 0;
}

int main() {
    MYSQL *conn;
    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[FIRST_NAME_LEN],
         last_name[LAST_NAME_LEN], email[EMAIL_LEN];
    char hashed_password[PASSWORD_LEN + 1];

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 0;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (insert_user(conn, username, hashed_password, first_name, last_name, email) == 0) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    mysql_close(conn);
    return 0;
}


To compile and run this code, you will need a MySQL server with the appropriate database (`testdb`) and table (`users`). The table should have columns for username, password, first_name, last_name, and email. Additionally, ensure that the MySQL C client library is installed on your system to link against it during compilation. Use the following command to compile:


gcc -o registration registration.c $(mysql_config --cflags --libs)


Replace `root` with your actual MySQL username and provide the necessary password if required. Adjust database connection details as needed.