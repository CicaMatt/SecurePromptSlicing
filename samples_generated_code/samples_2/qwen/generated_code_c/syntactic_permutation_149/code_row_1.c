#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 255

void insert_user_message_in_db(const char *username, const char *message) {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("messages.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO messages (username, message) VALUES ('%q', '%q');", username, message);
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    sqlite3_close(db);
}

void display_messages() {
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("messages.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    const char *sql = "SELECT username, message FROM messages;";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        printf("<html><body><h1>Messages</h1><ul>");
        while ((rc = sqlite3_step(res)) == SQLITE_ROW) {
            printf("<li>%s: %s</li>", sqlite3_column_text(res, 0), sqlite3_column_text(res, 1));
        }
        printf("</ul></body></html>");
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main() {
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";
    
    insert_user_message_in_db(username, message);
    
    printf("Content-type: text/html\n\n");
    display_messages();
    
    return 0;
}