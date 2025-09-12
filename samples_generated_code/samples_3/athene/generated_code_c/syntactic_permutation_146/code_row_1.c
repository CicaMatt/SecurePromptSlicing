#include <stdio.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void redirect_to_profile() {
    printf("Location: /profile.html\n\n");
}

int main() {
    char username[50], stock_name[50];
    int stock_quantity;
    sqlite3 *db;

    printf("Content-Type: text/html\n\n");

    printf("<form method='post'>"
           "Username: <input type='text' name='username'><br>"
           "Stock Name: <input type='text' name='stock_name'><br>"
           "Quantity: <input type='number' name='quantity'><br>"
           "<input type='submit'>"
           "</form>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "username=%[^&]&stock_name=%[^&]&quantity=%d", username, stock_name, &stock_quantity);

        sqlite3_open("database.db", &db);
        insert_buy_order(db, username, stock_name, stock_quantity);
        sqlite3_close(db);

        redirect_to_profile();
    }

    return 0;
}