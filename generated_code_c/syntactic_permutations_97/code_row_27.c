/* 
    This is the code for the login page
*/
#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include <string.h>
#define HASH_LENGTH 64                   // this constant represents the length of the hashed password
#define MAX_INPUT_LENGTH 255             // this constant represents the maximum input length of the user name and password
#define SALT_LENGTH 17 
int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "mysql";
    char *database = "mydb"; 

   /* 
      This is the code for opening a connection to the database server.
   */
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    // this is the code for creating a query to check if the username exists in the database
    char query[50] = "SELECT * FROM users WHERE Username='";
    strcat(query, username);
    strcat(query, "'");

    /* 
      This is the code that checks if the user name exists. If it does; a message saying that the username already exists is returned.
     */

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_store_result(conn);
    
   /* 
      this is the code that checks if the user name exists. If it does; a message saying that the username already exists is returned.
     */

    if (mysql_num_rows(res) > 0) {
        printf("User already exists\n");
    } else {
        /* 
            This code generates a random salt and adds it to the password before hashing it. The salt is then added to the database.
         */
        char salt[SALT_LENGTH];
        char hash[HASH_LENGTH];
        unsigned char rand_salt[17];
        RAND_bytes(rand_salt, sizeof rand_salt);
        snprintf(salt, SALT_LENGTH, "%02x", rand_salt);
        PKCS5_PBKDF2_HMAC((unsigned char *)password, strlen(password), (unsigned char *)salt, strlen(salt), 10000, EVP_sha512(), HASH_LENGTH, (unsigned char *)hash);

        /* 
            This code generates a random salt and adds it to the password before hashing it. The salt is then added to the database.
         */
        char insertQuery[100] = "INSERT INTO users(Username, Password, FirstName, LastName, Email) VALUES('";
        strcat(insertQuery, username);
        strcat(insertQuery, "', '");
        strcat(insertQuery, hash);
        strcat(insertQuery, "', '");
        strcat(insertQuery, firstname);
        strcat(insertQuery, "', '");
        strcat(insertQuery, lastname);
        strcat(insertQuery, "', '");
        strcat(insertQuery, email);
        strcat(insertQuery, "')");

        /* 
            This code inserts the username; hashed password; first name; last name; and email into the database.
         */
        if (mysql_query(conn, insertQuery)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        printf("Registration successful\n");
    }
    /* 
      This code closes the connection to the database.
     */
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}