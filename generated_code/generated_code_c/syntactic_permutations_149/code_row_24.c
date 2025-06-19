#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mysql/mysql.h"
#include "my_sql_connection.c"

struct user {
    char *name;
    int id;
};

void displayMessages(char *username) {
    MYSQL_RES *result = mysql_query("SELECT * FROM messages");
    if (result == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error());
        exit(1);
    }
    int numRows = mysql_num_rows(result);
    for (int i = 0; i < numRows; i++) {
        MYSQL_ROW row = mysql_fetch_row(result);
        printf("%s: %s\n", row[1], row[2]);
    }
}

void insertUserMessageInDb(char *username, char *message) {
    int id = -1;
    MYSQL_RES *result = mysql_query("SELECT * FROM users WHERE name = '%s'", username);
    if (result == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error());
        exit(1);
    }
    int numRows = mysql_num_rows(result);
    if (numRows > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        id = atoi(row[0]);
    } else {
        id = getId();
        mysql_query("INSERT INTO users VALUES ('%d', '%s')", id, username);
    }
    mysql_query("INSERT INTO messages VALUES ('%d', '%s', '%s')", id, username, message);
}

void handleRequest(char *username, char *message) {
    if (strcmp(message, "display") == 0) {
        displayMessages(username);
    } else {
        insertUserMessageInDb(username, message);
    }
}

int main() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<!DOCTYPE html>\n");
    printf("<html lang=\"en\">\n");
    printf("<body>\n");
    printf("<h1>Welcome to the chat</h1>\n");
    printf("You are logged in as %s<br>", username);
    printf("You can now send messages<br>");
    printf("Click <a href=\"/post\">here</a> to start chatting!");
    printf("</body>\n");
    printf("</html>\n");
}