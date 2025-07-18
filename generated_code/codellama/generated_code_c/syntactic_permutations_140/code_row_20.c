#include <mysql/mysql.h>

bool isUserExists(const char* userName) {
    bool result = false;
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, "localhost", "root", "password", "databaseName", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(con), mysql_error(con));
        return false;
    }

    MYSQL_RES* res = mysql_store_result(con);
    if (res) {
        int numRows = mysql_num_rows(res);
        if (numRows > 0) {
            result = true;
        } else {
            result = false;
        }
    }

    mysql_free_result(res);
    mysql_close(con);
    return result;
}