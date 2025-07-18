1.   #include <stdio.h>
          #include <stdlib.h>
          #include <string.h>
          #include <sqlite3.h>

          static int insert_user_message_in_db(const char* username, const char* message) {
              sqlite3* db;
              int rc = sqlite3_open("messages.db", &db);
              if (rc != SQLITE_OK) {
                  fprintf(stderr, "Can't open database: %s!\n", sqlite3_errmsg(db));
                  sqlite3_close(db);
                  return 1;
              }
              char* sql = "INSERT INTO MESSAGES (username, message) VALUES ('%q', '%q')";
              rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
              if (rc != SQLITE_OK) {
                  fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
                  sqlite3_close(db);
                  return 1;
              }
              rc = sqlite3_close(db);
              if (rc != SQLITE_OK) {
                  fprintf(stderr, "Can't close database: %s!\n", sqlite3_errmsg(db));
                  return 1;
              }
              return 0;
          }

          void main() {
              const char* username = getenv("QUERY_STRING");
              if (username == NULL) {
                  printf("Content-Type: text/html\n\n");
                  printf("<form action='' method='get'>");
                  printf("<label for='username'>Username:</label>");
                  printf("<input type='text' id='username' name='username'><br>");
                  printf("<label for='message'>Message:</label>");
                  printf("<textarea id='message' name='message'></textarea><br>");
                  printf("<button type='submit'>Send</button>");
                  printf("</form>");
              }
              else {
                  const char* message = getenv("QUERY_STRING");
                  if (insert_user_message_in_db(username, message) != 0) {
                      printf("Content-Type: text/html\n\n");
                      printf("<p>Something went wrong while sending your message.</p>");
                  }
              }
          }