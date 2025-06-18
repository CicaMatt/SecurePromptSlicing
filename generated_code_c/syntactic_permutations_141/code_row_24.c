#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <flask/flask.h>
#include <flask/jsonify.h>
#include <flask/request.h>

MYSQL *get_db_connection();
const char *get_server_name();
const char *get_user();
const char *get_password();

int main() {
    MYSQL *conn;
    conn = get_db_connection();

    const char *server_name = get_server_name();
    const char *username = get_user();
    const char *password = get_password();

    app.run(debug=True)
}