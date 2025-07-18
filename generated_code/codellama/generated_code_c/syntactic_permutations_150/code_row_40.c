#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int insert_user_message_in_db(const char* username, const char* message);
void post(request *req) {
    char *username = req->get_param("username");
    char *message = req->get_param("message");
    int rc = insert_user_message_in_db(username, message);
    if (rc != 0) {
        printf("Failed to insert the message into the database: %s\n", sqlite3_errmsg(db));
    }
    redirect("/");
}