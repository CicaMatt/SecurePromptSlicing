#include <mysql/mysql.h>
    #include <string.h>

    char* getMaxTemperature(int latitude, int year, int month, int day) {
        MYSQL *conn;
        char query[1024];
        sprintf(query, "SELECT temperature FROM weather WHERE latitude = %d AND year = %d AND month = %d AND day = %d ORDER BY temperature DESC LIMIT 1", latitude, year, month, day);
        MYSQL_RES *res;
        MYSQL_ROW row;
        conn = mysql_init(NULL);
        if (conn == NULL) {
            return "Error";
        }
        if (mysql_real_connect(conn, "localhost", "root", "", "weather", 3306, NULL, 0) == NULL) {
            return "Error";
        }
        if (mysql_query(conn, query)) {
            return "Error";
        }
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        mysql_close(conn);
        return row[0];
    }