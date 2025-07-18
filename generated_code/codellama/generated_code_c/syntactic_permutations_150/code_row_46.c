#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int insert_user_message_in_db(const char *username, const char *message)
{
  sqlite3 *db;
  sqlite3_stmt *res;
  int rc = sqlite3_open("chat.db", &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  }

  char *sql = "INSERT INTO messages (username, message) VALUES (@username, @message);";
  rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  }

  sqlite3_bind_text(res, 1, username, -1, NULL);
  sqlite3_bind_text(res, 2, message, -1, NULL);

  rc = sqlite3_step(res);

  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to step: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return -1;
  }

  rc = sqlite3_finalize(res);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to finalize: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  }

  rc = sqlite3_close(db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  return 0;
}

void post()
{
  const char *username = getenv("REQUEST_METHOD");
  const char *message = getenv("QUERY_STRING");

  if (insert_user_message_in_db(username, message) != 0) {
    printf("Status: 500 Internal Server Error\r\n");
    printf("\r\n");
    printf("Failed to insert message into database");
    return;
  }

  printf("Status: 302 Found\r\n");
  printf("Location: http://localhost:8080/\r\n");
  printf("\r\n");
}