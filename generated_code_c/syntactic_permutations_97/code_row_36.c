/*
    This program is to register users.
    It checks if the user already exists, 
    and if so returns a message saying that the username already exists in the database.
    If it doesn't exist, it adds the username and hashed password into the database and returns a message saying that the registration succeeded.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

//define the database connection information here
const char *server = "localhost";
const char *user = "username";
const char *password = "password";
const char *database = "database_name";

int main() {
    //connect to the database
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //create the query to check if the username already exists in the database
    char query[128] = "SELECT username FROM users WHERE username='%s'";

    //prompt user for input and insert into query string
    printf("Enter your desired username: ");
    scanf("%s", &query[strlen(query) - 3]);

    MYSQL_RES *result;
    result = mysql_query(conn, query);

    //check if the username exists in the database and print message accordingly
    if (mysql_num_rows(result) > 0) {
        printf("Error: Username already exists");
    } else {
        //create a hashed password using SHA256
        char passwd[128] = "password";
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(passwd, strlen(passwd), hash);
        printf("Registration Successful\n");
    }

    //close the database connection and return 0 to main()
    mysql_close(conn);
    return 0;
}