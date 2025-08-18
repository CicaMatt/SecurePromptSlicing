#include <stdio.h>
#include <sqlite3.h>

void handle_form_submission(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Location: /stock_view\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/stock_view\"></head></html>");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Content-Type: text/html\n\n");

    printf("<form method='post'>");
    printf("Stock Name: <input type='text' name='stock_name'><br>");
    printf("Quantity: <input type='number' name='quantity'><br>");
    printf("<input type='submit' value='Submit'></form>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "stock_name=%[^&]&quantity=%d", stock_name, &quantity);

        handle_form_submission(stock_name, quantity);

        free(data);
    }

    return 0;
}