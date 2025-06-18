#include <mysql/mysql.h>
    
    MYSQL *connect() {
        MYSQL *conn = mysql_init(NULL);
        
        //connection parameters
        if (!mysql_real_connect(conn, "localhost", "username", "password",
                                "database name", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return NULL;
        }
    
        //if connection successful
        printf("Connection established.\n");
        
        //return the connection handler
        return conn;
    }
    
    int usernameExists(MYSQL *conn, const char *username) {
        //check if the username exists in the database
        const char query[] = "SELECT * FROM users WHERE username = '?'";
        
        //prepare the statement for execution
        MYSQL_STMT *stmt;
        stmt = mysql_stmt_init(conn);
        if (!stmt) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
        }
        
        //prepare the statement for execution
        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
        }
        
        //bind the parameter to the placeholder in the query
        MYSQL_BIND params[1];
        memset(params, 0, sizeof(params));
        
        char buffer[256];
        strcpy(buffer, username);
        
        ulong length = strlen(username);
        
        params[0].buffer_type = MYSQL_TYPE_STRING;
        params[0].buffer = (char *) buffer;
        params[0].is_null = 0;
        params[0].length = &length;
        
        if (mysql_stmt_bind_param(stmt, params)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
        }
        
        //execute the statement and get the result
        MYSQL_BIND result[1];
        memset(result, 0, sizeof(result));
        
        char usernameResult[256];
        unsigned long lengthResult;
        
        result[0].buffer_type = MYSQL_TYPE_STRING;
        result[0].buffer = (char *) usernameResult;
        result[0].is_null = 0;
        result[0].length = &lengthResult;
        
        if (mysql_stmt_bind_result(stmt, result)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
        }
        
        //execute the statement and get the result
        if (mysql_stmt_execute(stmt)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
        }
        
        //get the row from the result set
        MYSQL_ROW row = mysql_fetch_row(stmt->result);
        if (row) {
            //the username exists in the database
            return 1;
        } else {
            //the username does not exist in the database
            return 0;
        }
    }
    
    int main() {
        //connect to the database
        MYSQL *conn = connect();
        
        //check if the connection was successful
        if (!conn) {
            printf("Failed to establish a connection to the MySQL Server.\n");
        } else {
            //check if the username exists in the database
            const char *username = "admin";
            
            int result = usernameExists(conn, username);
            if (result == 1) {
                printf("Username %s exists in the database.\n", username);
            } else {
                printf("Username %s does not exist in the database.\n", username);
            }
            
            //close the connection
            mysql_free_result(conn->result);
            mysql_stmt_close(conn->stmts);
            mysql_close(conn);
        }
        
        return 0;
    }