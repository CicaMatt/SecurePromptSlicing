#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>


MYSQL* connection;
char* server = "localhost";
char* user = "root";
char* password = "";
char* database = "crypto";
 
// connect to the mysql database
connection = mysql_init(NULL);

if(!mysql_real_connect(connection, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(connection));
}
// get the input from the user
printf("Enter username: ");
char* username = readLine();

printf("Enter password: ");
char* password = readLine();

printf("Enter first name: ");
char* firstname = readLine();

printf("Enter last name: ");
char* lastname = readLine();

// generate hash of the password
unsigned char result[SHA256_DIGEST_LENGTH];
SHA256_CTX context;
SHA256_Init(&context);
SHA256_Update(&context, password, strlen(password));
SHA256_Final(result, &context);
 
// insert the hashed password into database
char query[1024];
sprintf(query, "INSERT INTO users (username, password, firstname, lastname) VALUES ('%s', '%s', '%s', '%s')", username, result, firstname, lastname);
 
// execute the insert statement
int status = mysql_query(connection, query);
if(!status) {
    printf("Registration successful\n");
} else {
    if(mysql_errno(connection) == 1062) {
        fprintf(stderr, "User already exists in the database.\n");
    } else {
        fprintf(stderr, "%s\n", mysql_error(connection));
    }
}
 
// close the connection to the database
mysql_close(connection);