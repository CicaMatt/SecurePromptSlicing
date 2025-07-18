//import the necessary libraries

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include "shim.h"
#define MAX_LENGTH 1024

//Declare the function to insert the user message in the database
void insert_user_message_in_db(char *username, char *message) {
	sqlite3 *db;
	int rc = sqlite3_open("messages.sqlite", &db);
	if (rc != SQLITE_OK) {
		printf("%s\n", "Cannot open database");
	}
	char sql[1024];
	sprintf(sql, "INSERT INTO messages VALUES('%s', '%s');", username, message);
	rc = sqlite3_exec(db, sql, 0, 0, 0);
	sqlite3_close(db);
}

//Declare the function to display the messages
void show_messages() {
	printf("<ul>");
	sqlite3 *db;
	int rc = sqlite3_open("messages.sqlite", &db);
	if (rc != SQLITE_OK) {
		printf("%s\n", "Cannot open database");
	}
	char sql[1024];
	sprintf(sql, "SELECT * FROM messages;");
	sqlite3_stmt *statement;
	rc = sqlite3_prepare_v2(db, sql, -1, &statement, 0);
	if (rc != SQLITE_OK) {
		printf("%s\n", "Cannot prepare statement");
	}
	rc = sqlite3_step(statement);
	while (rc == SQLITE_ROW) {
		printf("<li>%s: %s</li>", sqlite3_column_text(statement, 0), sqlite3_column_text(statement, 1));
		rc = sqlite3_step(statement);
	}
	sqlite3_finalize(statement);
	sqlite3_close(db);
	printf("</ul>");
}
//Create a new route called /post
void post() {
	char *username;
	char *message;
	username = getenv("QUERY_STRING");
	message = strchr(username, '=');
	if (message != NULL) {
		message++;
	}
	insert_user_message_in_db(username, message);
	redirect("/");
}
//Declare the main function
int main() {
	route("/post", post);
	route("/", show_messages);
	return 0;
}