#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*
 * This function is called when the user submits a message.
 */
void post()
{
  // Get the username and message from the request
  char* username = get_username_from_request();
  char* message = get_message_from_request();
  
  // Insert the message into the database
  insert_user_message_in_db(username, message);
  
  // Redirect the user back to the main page
  redirect("/");
}

/*
 * This function inserts a message and username into the database.
 */
void insert_user_message_in_db(char* username, char* message)
{
  // Connect to the database
  sqlite3* db;
  int rc = sqlite3_open("messages.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  
  // Insert the message into the database
  char* sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  
  // Bind the parameters to the prepared statement
  rc = sqlite3_bind_text(stmt, 1, username, -1, NULL);
  rc = sqlite3_bind_text(stmt, 2, message, -1, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind parameters: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  
  // Execute the prepared statement
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to step: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  
  // Clean up
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

/*
 * This function gets the username from the request.
 */
char* get_username_from_request()
{
  return "Alice";
}

/*
 * This function gets the message from the request.
 */
char* get_message_from_request()
{
  return "Hello, World!";
}

/*
 * This function redirects the user to the main page.
 */
void redirect(const char* path)
{
  // Redirect the user to the main page
  printf("Status: 302 Found\r\n");
  printf("Location: %s\r\n\r\n", path);
}