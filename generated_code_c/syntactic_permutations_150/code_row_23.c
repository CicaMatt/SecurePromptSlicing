#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include "sqlite3.h"

#define SQLITE_DB "messages.db"
#define TABLE_NAME "messages"
#define COLUMN_ID "id"
#define COLUMN_USERNAME "username"
#define COLUMN_MESSAGE "message"
#define INSERT_SQL_STATEMENT "INSERT INTO %s(%s, %s) VALUES ('%s', '%s')"
#define SELECT_SQL_STATEMENT "SELECT * FROM %s ORDER BY %s ASC"

sqlite3* db;

int insert_user_message_in_db(const char* username, const char* message) {
  int result = 0;
  sqlite3_stmt* stmt;
  char sql[256];
  sprintf(sql, INSERT_SQL_STATEMENT, TABLE_NAME, COLUMN_USERNAME, COLUMN_MESSAGE, username, message);
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    result = sqlite3_step(stmt);
  } else {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
  }
  return result;
}

void post() {
  const char* username = getenv("QUERY_STRING");
  const char* message = getenv("HTTP_USER_MESSAGE");
  if (insert_user_message_in_db(username, message) != SQLITE_OK) {
    fprintf(stderr, "Failed to insert message: %s\n", sqlite3_errmsg(db));
  } else {
    printf("Content-type: text/html\r\n\r\n");
    printf("<html><head>Posted!</head>");
    printf("<body>Message posted successfully.</body></html>");
  }
}

void main() {
  if (getenv("REQUEST_METHOD") == "POST") {
    post();
  } else {
    printf("Content-type: text/html\r\n\r\n");
    printf("<html><head>Hello</head><body>");
    printf("<form action='%s' method='post'>", getenv("SCRIPT_NAME"));
    printf("<input type='text' name='username'/><br/>");
    printf("<textarea name='message'></textarea><br/>");
    printf("<input type='submit' value='Post'/>");
    printf("</form></body></html>");
  }
}