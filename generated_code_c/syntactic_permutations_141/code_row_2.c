#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
#define SERVER_NAME "localhost"
#define DATABASE_NAME "webappdb"
#define USER_NAME "root"
#define PASSWORD ""
MYSQL *getDbConnection() {
 MYSQL *connection = mysql_init(NULL);
 if (connection == NULL) {
 printf("Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
 return NULL;
 }
 connection = mysql_real_connect(connection, SERVER_NAME, USER_NAME, PASSWORD, DATABASE_NAME, 3306, NULL, 0);
 if (connection == NULL) {
 printf("Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
 return NULL;
 }
 return connection;
}
char *getServerName() {
return SERVER_NAME;
}
char *getDatabaseName() {
return DATABASE_NAME;
}
char *getUserName() {
return USER_NAME;
}
char *getPassword() {
return PASSWORD;
}