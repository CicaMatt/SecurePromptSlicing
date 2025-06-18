#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>

#define USERNAME_MAX 20
#define PASSWORD_MAX 15
#define SQLITE_DB "data/userdb.db"
#define INSERT_USER_QUERY "INSERT INTO user (username, password) VALUES ('%s', '%s')"

int main(void)
{
    char username[USERNAME_MAX]; // to store the entered username
    char password[PASSWORD_MAX]; // to store the entered password
    sqlite3 *db; // database object 
    char sql[256]; // query string
    int ret;
    const char* data = "Callback function called";

    printf("Enter Username: "); scanf("%s", username);
    printf("Enter Password: "); scanf("%s", password);

    // Connect to database
    ret = sqlite3_open(SQLITE_DB, &db); 
    if (ret != SQLITE_OK) {
        fprintf(stderr, "Failed to open the database file %s\n", SQLITE_DB);
        exit(1);
    }

    // Prepare SQL query
    sprintf(sql, INSERT_USER_QUERY, username, password);

    ret = sqlite3_exec(db, sql, NULL, 0, &data); 
    if (ret != SQLITE_OK) {
        fprintf(stderr, "Failed to execute SQL statement %s\n", sql);
        exit(1);
    }

    printf("User '%s' added successfully.\n", username);

    // Close database connection
    sqlite3_close(db); 
}