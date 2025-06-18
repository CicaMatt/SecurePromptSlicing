#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // SQLITE3 - https://www.sqlite.org/download.html
    #include "sqlite3.h"

    int main() {
      sqlite3 *db; // database object pointer
      char *err_msg = 0;
      int rc;

      rc = sqlite3_open("database.db", &db);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
      }

      char *sql = "SELECT is_moderator FROM users WHERE user_id=?";
      sqlite3_stmt *stmt;

      rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
      }

      // bind parameters - user id
      int user_id = 100;
      rc = sqlite3_bind_int(stmt, 1, user_id);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
      }

      int step = sqlite3_step(stmt);
      if (step != SQLITE_ROW) {
        fprintf(stderr, "Query failed\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
      }

      // get result - is moderator
      int is_moderator = sqlite3_column_int(stmt, 0);
      printf("Is moderator: %d\n", is_moderator);

      sqlite3_finalize(stmt);
      sqlite3_close(db);

      return 0;
    }