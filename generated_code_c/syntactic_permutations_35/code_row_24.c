<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        <label for="username">Username: </label>
        <input type="text" name="username"><br><br>
        <label for="password">Password: </label>
        <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>


// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc = 0;
    char *err_msg = 0;
    const char *sql = "SELECT username, password FROM login";
    sqlite3_stmt *stmt;
    
    // open database
    rc = sqlite3_open("login.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // prepare the select statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // step through the result set
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const char *username = (const char *)sqlite3_column_text(stmt, 0);
        printf("%s\n", username);
        
        const char *password = (const char *)sqlite3_column_text(stmt, 1);
        if (!strcmp(password, password)) {
            printf("Username and password match!\n");
            
            // redirect to home page
            fprintf(stderr, "Redirecting to home page\n");
            return 0;
        } else {
            fprintf(stderr, "Incorrect username or password.\n");
            return 1;
        }
    }
    
    // free the memory
    sqlite3_finalize(stmt);
    
    // close the database
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    return 0;
}