#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void redirect_to_profile() {
    printf("Location: /profile.html\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>You have been redirected to the profile page.</body></html>");
}

int insert_into_database(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO user_stocks (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

int main() {
    char *username = getenv("HTTP_COOKIE"); // Assuming username is stored in a cookie
    if (username == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login required.</body></html>");
        return 1;
    }

    char stock_name[50];
    int stock_quantity;

    // Read form data
    char *form_data = getenv("QUERY_STRING");
    if (sscanf(form_data, "stock_name=%49[^&]&stock_quantity=%d", stock_name, &stock_quantity) != 2) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid form data.</body></html>");
        return 1;
    }

    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Database error.</body></html>");
        return 1;
    }

    rc = insert_into_database(db, username, stock_name, stock_quantity);
    if (rc != 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Failed to add stock to database.</body></html>");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    redirect_to_profile();
    return 0;
}