#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(const char *payload, MYSQL *conn) {
    double latitude = 0.0;
    double longitude = 0.0;
    char date[11] = {0};

    sscanf(payload, "{\"latitude\": %lf, \"longitude\": %lf, \"date\": \"%10[^\"]\"}", &latitude, &longitude, date);

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    if ((MYSQL_ROW row = mysql_fetch_row(result))) {
        printf("{\"temperature\": %s}\n", row[0]);
    } else {
        printf("{\"error\": \"No data found\"}\n");
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *payload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-01\"}";
    handle_request(payload, conn);

    mysql_close(conn);
    return 0;
}