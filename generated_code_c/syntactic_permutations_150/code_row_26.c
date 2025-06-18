#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sqlite3.h>
#include<pthread.h>

void insert_user_message_in_db(char *username, char *message);
int main()
{
    char *username = "mario";
    char *message = "This is a test message.";
    insert_user_message_in_db(username,message);

}
void insert_user_message_in_db(char *username, char *message)
{
    sqlite3 *db; 
    int rc;

    /* Open database */
    rc = sqlite3_open("messages.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[] = "INSERT INTO Messages VALUES(NULL, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc) {
        fprintf(stderr, "Can't prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind values to parameters
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc) {
        fprintf(stderr, "Can't bind value: %s\n", sqlite3_errmsg(db));
        return;
    }
    rc = sqlite3_bind_text(stmt, 2, message, -1, SQLITE_STATIC);
    if (rc) {
        fprintf(stderr, "Can't bind value: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Execute statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Message inserted successfully!\n");
    } else {
        fprintf(stderr, "Can't execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize and close database
    sqlite3_finalize(stmt);
    rc = sqlite3_close(db);
    if (rc) {
        fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
        return;
    }
}