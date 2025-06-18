#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
// function to connect to mysql database using environment variables
MYSQL *db_connect() {
  MYSQL *conn;
  char host[1024], user[1024], password[1024], db[1024];
  int port;
  // get the credentials from environment variables
  getenv("DB_HOST",host);
  getenv("DB_USER",user);
  getenv("DB_PASSWORD",password);
  getenv("DB_NAME",db);
  port = atoi(getenv("DB_PORT"));
  
  conn = mysql_init(NULL);
  if(!mysql_real_connect(conn, host, user, password, db, port, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return NULL;
  }
  return conn;
}
// function to execute sql query
int execute_query(MYSQL *conn, char *sql) {
  int status = mysql_query(conn, sql);
  if (status !=0){
    fprintf(stderr, "%s\n", mysql_error(conn));
    return -1;
  }
  return 0;
}
// function to check user moderator status
int is_moderator(MYSQL *conn, char* username) {
  int status = 0;
  char sql[256];
  sprintf(sql,"SELECT role FROM users WHERE name='%s'", username);
  if (execute_query(conn, sql))
    return -1;
  MYSQL_RES *res = mysql_use_result(conn);
  int num_fields = mysql_num_fields(res);
  if (num_fields ==0)
    return -2;
  char row[num_fields][1024];
  while ((row = mysql_fetch_row(res)) !=NULL) {
    if (!strcmp("moderator", row[0])) {
      status = 1;
      break;
    }
  }
  return status;
}
int main() {
  MYSQL *conn = db_connect();
  char username[1024];
  // get the username from stdin
  scanf("%s",username);
  int isMod = is_moderator(conn, username);
  if (isMod ==1) {
    printf("True");
  } else {
    printf("False");
  }
  mysql_close(conn);
}