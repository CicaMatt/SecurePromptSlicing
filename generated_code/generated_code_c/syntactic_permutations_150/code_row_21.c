// Include necessary libraries.
#include <stdio.h> // for printf() and scanf() functions
#include <stdlib.h> // for exit() function
#include <string.h> // for strlen() function
#include <sqlite3.h> // for sqlite3_* functions
#include <time.h> // for time() function

// Define variables and constants.
static int callback(void *data, int argc, char **argv, char **azColName);
int insert_user_message_in_db(const char *username, const char *message) {
  sqlite3 *db; // database object
  char *error = 0; // error message
  int rc = 0; // return code
  char sql[256]; // SQL statement
  sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s');", username, message);
  rc = sqlite3_exec(db, sql, callback, 0, &error);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", error);
    sqlite3_close(db);
    exit(1);
  }
  printf("Message inserted successfully.\n");
}
int main() {
  // Connect to database.
  int rc = sqlite3_open("messages.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  // Create a new message.
  char username[256];
  char message[256];
  printf("Enter your name: ");
  scanf("%s", username);
  printf("Enter your message: ");
  scanf("%s", message);
  insert_user_message_in_db(username, message);
  // Redirect user to main page.
  header('Location: index.html');
}