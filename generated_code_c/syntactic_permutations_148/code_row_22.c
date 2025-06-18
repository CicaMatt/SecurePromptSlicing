#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAX_BUFFER 65536
#define MAX_USERNAME 20
#define MAX_MESSAGE 140
void insert_user_message_in_db(char *username, char *message) {
   // Connect to the database.
    sqlite3 *db;
    if (sqlite3_open("chat.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database.\n");
        exit(1);
    }
    char sql[256];
   // Create the SQL statement and execute it.
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s');", username, message);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
    sqlite3_close(db);
}
void post() {
   // Get the username and message from the request.
    char username[MAX_USERNAME];
    char message[MAX_MESSAGE];
    fgets(username, MAX_USERNAME, stdin);
    fgets(message, MAX_MESSAGE, stdin);
    insert_user_message_in_db(username, message);
   // Redirect the user to the main page.
    char *html = "<html><head></head><body>You are now chatting with %s!</body></html>\n";
    printf(html, username);
}
int main() {
    post();
    return 0;
}