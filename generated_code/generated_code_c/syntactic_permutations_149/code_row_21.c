// C program to insert data in database and 
// fetch it back using SQL queries.
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
 
// Function to insert user message into the database.
void insert_user_message_in_db(char *username, char *message)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc, i;
    char sql[100];
 
    /* Open database */
    rc = sqlite3_open("database.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stdout, "Opened database successfully\n");
    }
 
    /* Create SQL statement */
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s');", username, message);
 
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}
 
// Function to fetch data from database.
void fetch_messages_from_db()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc, i;
    char sql[100];
    const char* data = "Callback function called";
 
    /* Open database */
    rc = sqlite3_open("database.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stdout, "Opened database successfully\n");
    }
 
    /* Create SQL statement */
    sprintf(sql, "SELECT * from messages;");
 
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}
 
// Callback function to print the fetched data.
static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
 
int main(int argc, char **argv)
{
    // To be used for user inputs.
    char username[25], message[200];
 
    // User prompt to input the data.
    printf("Enter your name: ");
    scanf("%s", &username);
    printf("Enter your message: ");
    scanf("%s", &message);
 
    insert_user_message_in_db(username, message);
    fetch_messages_from_db();
    return 0;
}