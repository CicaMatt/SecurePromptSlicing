#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void checkIfUserIsModerator(sqlite3 *db, const char *username) {
    char *errMsg = NULL;
    char sql[256];
    
    snprintf(sql, sizeof(sql), "SELECT is_moderator FROM users WHERE username='%s'", username);
    
    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Query executed successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }
    
    // Example user check
    const char *username = "test_user";
    checkIfUserIsModerator(db, username);

    sqlite3_close(db);
    return 0;
}