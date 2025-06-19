#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include <mysql/mysql.h>
    #define SERVER "localhost"
    #define USER "root"
    #define PASSWORD "password" /* replace with an appropriate password */
    #define DATABASE "subscribers"

    void delete_user(MYSQL*);

    int main() {
      MYSQL *conn = mysql_init(NULL);
  
      if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
        return 1;
      }
  
      delete_user(conn);
      mysql_close(conn);
      return 0;
    }

    void delete_user(MYSQL *conn) {
      char email[50];
      printf("Enter the email you want to unsubscribe: ");
      scanf("%s", email);
  
      if (is_subscribed(email, conn)) {
        MYSQL_STMT* statement = mysql_stmt_init(conn);
        const char* query = "DELETE FROM subscribers WHERE email=?";
        if (mysql_stmt_prepare(statement, query, strlen(query)))
          fprintf(stderr, "Failed to prepare statement: %s\n", mysql_error(conn));
  
        MYSQL_BIND params[1];
        memset(params, 0, sizeof(params));
  
        char email_param[50] = email;
        params[0].buffer_type = MYSQL_TYPE_STRING;
        params[0].buffer = email_param;
        params[0].is_null = 0;
        if (mysql_stmt_bind_param(statement, params)) {
          fprintf(stderr, "Failed to bind parameters: %s\n", mysql_error(conn));
          return;
        }
  
        if (mysql_stmt_execute(statement))
          fprintf(stderr, "Error executing statement: %s\n", mysql_error(conn));
        else {
          printf("User with email address '%s' has been unsubscribed.\n", email);
          return;
        }
      }
    }

    int is_subscribed(char* email, MYSQL* conn) {
      char query[200] = "SELECT COUNT(*) FROM subscribers WHERE email='";
      strcat(query, email);
      strcat(query, "'");
  
      if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 0;
      }
  
      MYSQL_RES* result = mysql_store_result(conn);
      MYSQL_ROW row = mysql_fetch_row(result);
      int subscribed = atoi(*row);
      if (subscribed) {
        printf("User with email address '%s' is already subscribed.\n", email);
        return 1;
      } else {
        printf("User with email address '%s' is not subscribed.\n", email);
        return 0;
      }
    }