#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <mysql/mysql.h> 
#define SERVER "localhost" 
#define USER "root" 
#define PASSWORD "password"
#define DBNAME "userpassdb"

int main() { 
 char username[50]; 
 char password[50]; 
 MYSQL *conn; 
 MYSQL_RES *res;
 MYSQL_ROW row;
 char query[200], hashedpass[100]; 
  printf("Username: ");
  scanf("%s", username); 
  printf("Password: ");
  scanf("%s", password);

  conn = mysql_init(NULL); 
  if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DBNAME, 0, NULL, 0)) { 
    printf("Connection failed\n");
    return 1;
  }

  sprintf(query, "INSERT INTO users(username, password) VALUES('%s', '%s')", username, password);
  mysql_real_query(conn, query, strlen(query)); 
  printf("User added successfully\n");
  return 0;
}