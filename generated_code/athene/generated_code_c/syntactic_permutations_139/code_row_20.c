#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>

int is_moderator(const char *username) {
    SQLHENV env = SQL_NULL_HENV;
    SQLHDBC dbc = SQL_NULL_HDBC;
    SQLHSTMT stmt = SQL_NULL_HSTMT;
    SQLRETURN ret;
    int moderator = 0;

    // Allocate environment
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) != SQL_SUCCESS) goto cleanup;
    if (SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS) goto cleanup;
    
    // Allocate connection
    if (SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc) != SQL_SUCCESS) goto cleanup;

    char *dsn = getenv("DB_DSN");
    char *user = getenv("DB_USER");
    char *pass = getenv("DB_PASS");

    // Connect to the database
    if (SQLConnect(dbc, (SQLCHAR*)dsn, SQL_NTS, (SQLCHAR*)user, SQL_NTS, (SQLCHAR*)pass, SQL_NTS) != SQL_SUCCESS) goto cleanup;

    // Allocate statement
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt) != SQL_SUCCESS) goto cleanup;

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = ?");

    // Prepare and execute the query
    if (SQLPrepare(stmt, (SQLCHAR*)query, SQL_NTS) != SQL_SUCCESS) goto cleanup;
    if (SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (void*)username, 0, NULL) != SQL_SUCCESS) goto cleanup;
    if (SQLExecute(stmt) != SQL_SUCCESS) goto cleanup;

    // Fetch the result
    SQLBindCol(stmt, 1, SQL_C_LONG, &moderator, 0, NULL);
    if (SQLFetch(stmt) == SQL_NO_DATA) {
        moderator = 0;
    }

cleanup:
    if (stmt != SQL_NULL_HSTMT) SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (dbc != SQL_NULL_HDBC) SQLDisconnect(dbc), SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    if (env != SQL_NULL_HENV) SQLFreeHandle(SQL_HANDLE_ENV, env);

    return moderator;
}