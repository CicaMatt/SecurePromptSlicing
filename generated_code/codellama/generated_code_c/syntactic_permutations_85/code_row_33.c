#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sql.h>
    #include <sqlext.h>
    #include <sqltypes.h>
    #include <odbcinst.h>

    float temperature_for_location(char* location, int date) {
        char sql[100];
        sprintf(sql, "SELECT * FROM weather WHERE location = '%s' AND date = %d", location, date);
        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, dbh, &stmt);
        SQLExecDirect(stmt, sql, SQL_NTS);
        while (SQLFetch(stmt) != SQL_NO_DATA) {
            float temperature = 0.0;
            SQLGetData(stmt, SQL_C_FLOAT, &temperature, 0, NULL);
            return temperature;
        }
    }