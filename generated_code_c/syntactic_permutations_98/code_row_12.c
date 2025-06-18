#include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <mysql/mysql.h>
 
 // define database connection information
 #define DB_HOST "localhost"
 #define DB_USER "root"
 #define DB_PASSWORD ""
 #define DB_DATABASE "userdb"
 
 int main() {
     MYSQL *conn;
     MYSQL_RES *res;
     MYSQL_ROW row;
     char *server = DB_HOST;
     char *username = DB_USER;
     char *password = DB_PASSWORD;
     char *database = DB_DATABASE;
 
     // connect to database
     conn = mysql_init(NULL);
     if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
         printf("Error connecting to database. \n");
         return -1;
     }
 
     // create table if it does not exist
     char *create_table = "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255), password VARCHAR(255))";
     if (mysql_query(conn, create_table)) {
         printf("Error creating table. \n");
         return -1;
     }
 
     // register user
     char username[50];
     char password[50];
     printf("Enter Username: ");
     scanf("%s", &username);
     printf("Enter Password: ");
     scanf("%s", &password);
 
     // hash password
     unsigned char hash[64];
     char *hashed_password = NULL;
     sha512(password, strlen(password), hash);
     for (int i = 0; i < sizeof(hash); i++) {
         sprintf(&hashed_password, "%s%02x", hashed_password, hash[i]);
     }
 
     // insert user into database
     char *insert_user = "INSERT INTO users (username, password) VALUES ('%s', '%s')";
     if (mysql_query(conn, insert_user)) {
         printf("Error inserting user. \n");
         return -1;
     }
 
     // display message
     printf("User registered successfully. \n");
 
     // close database connection
     mysql_close(conn);
 
     return 0;
 }