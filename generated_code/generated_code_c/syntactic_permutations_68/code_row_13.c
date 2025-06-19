include <stdio.h>
include <stdlib.h>
include "sqlite3.h"
include "base64.h"
include "fileio.h"

int upload_image(char *name, char *data, int size) {
  sqlite3 *db; // SQLite database struct
  sqlite3_stmt *stmt; // SQL statement struct
  int rc; // Return code from SQLite functions
  const char sql[] = "INSERT INTO images (name, data) VALUES (?, ?);"; // SQL query

  // Open the database connection
  rc = sqlite3_open("images.db", &db);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // Prepare the SQL statement
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare SQL: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // Bind the values to the placeholders in the prepared statement
  rc = sqlite3_bind_text(stmt, 1, name, -1, NULL);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind value: %s\n", sqlite3_errmsg(db));
    return -1;
  }
  
  // Convert the image data from raw bytes into a base64 string
  char *base64 = malloc(size);
  base64_encode(data, size, base64, &size);
  rc = sqlite3_bind_text(stmt, 2, base64, -1, NULL);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind value: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // Execute the prepared statement to insert the data into the database
  rc = sqlite3_step(stmt);
  if(rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to execute SQL: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // Finalize the prepared statement and close the database connection
  rc = sqlite3_finalize(stmt);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to finalize SQL: %s\n", sqlite3_errmsg(db));
    return -1;
  }
  
  rc = sqlite3_close(db);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // Return success
  return 0;
}