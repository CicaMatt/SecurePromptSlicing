#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "mydatabase"
 
int main()
{
    // create a mysql connection handle
    MYSQL *conn = mysql_init(NULL);
 
    // connect to the database
    if (mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
    {
        printf("Connected to database\n");
    }
    else
    {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    }
 
    // create a hashed password using SHA256 algorithm
    char *password = "mysecretpassword";
    int password_length = strlen(password);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, password_length);
    SHA256_Final(hash, &sha256);
 
    // create a query to insert the username and hashed password into the database
    char *query = "INSERT INTO users (username, password) VALUES ('admin', '";
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        query = strcat(query, hash[i]);
    }
    query = strcat(query, "')");
 
    // execute the query
    if (mysql_real_query(conn, query, strlen(query)))
    {
        fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
        return 1;
    }
 
    // close the connection to the database
    mysql_close(conn);
    printf("Closed connection to database\n");
    return 0;
}

### Concept:
C language, SHA256 hash algorithm, MySQL database.