#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <stddef.h>
#include <string.h>

int login(char username[], char password[]);

int main() {
  char username[256];
  char password[256];
  
  printf("Enter username: ");
  scanf("%s", &username);

  printf("Enter password: ");
  scanf("%s", &password);

  int status = login(username, password)
  if (status == 1) {
    return 0;
  } else if (status == 2) {
    printf("Incorrect username or password. Try again.\n");
  } else {
    printf("Unknown error. Try again later.\n");
  }
}

int login(char username[], char password[]) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc, status = -1;
  
  const char* data = "Callback function called";
  sqlite3_stmt *pStmt;

  /* Open database */
  rc = sqlite3_open("login.db", &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }

  /* Create SQL statement */
  char sql[256];
  sprintf(sql, "SELECT * FROM users WHERE username = \"%s\"", username);
  
  rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
  if (rc == SQLITE_OK) {
    while ((rc = sqlite3_step(pStmt)) == SQLITE_ROW) {
      char *user_password;
      strcpy(user_password, sqlite3_column_text(pStmt, 1));
      if (strcmp(user_password, password) == 0) {
        status = 1;
        break;
      } else {
        status = 2;
        break;
      }
    }
  } else {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
  }

  /* Close database */
  rc = sqlite3_close(db);
  if (rc) {
    fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
    return -1;
  } else {
    fprintf(stdout, "Closed database successfully\n");
  }
  
  return status;
}