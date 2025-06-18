#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    
    /*
     * Function to buy stock
     */
    void buy_stock(const char *name, int quantity)
    {
        // Create a database connection
        SQLHENV env;
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
        SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
        SQLHDBC dbc;
        SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
        SQLDriverConnect(dbc, NULL, "DSN=stocks", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
     
        // Check if the stock exists
        char query[256];
        sprintf(query, "SELECT COUNT(*) FROM STOCKS WHERE NAME = '%s'", name);
        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
        SQLExecDirect(stmt, query, SQL_NTS);
     
        // Insert the stock into the database
        if (SQLFetch(stmt) == SQL_SUCCESS)
        {
            int count = SQLGetData(stmt, 1, SQL_C_LONG, NULL, 0, NULL);
            if (count == 0)
            {
                sprintf(query, "INSERT INTO STOCKS VALUES ('%s', %d)", name, quantity);
                SQLExecDirect(stmt, query, SQL_NTS);
            }
            else
            {
                // Update the stock quantity
                sprintf(query, "UPDATE STOCKS SET QUANTITY = %d WHERE NAME = '%s'", quantity + count, name);
                SQLExecDirect(stmt, query, SQL_NTS);
            }
        }
     
        // Close the database connection
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        SQLDisconnect(dbc);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
    }
     
    /*
     * Function to handle buy button clicks
     */
    void on_buy_button_clicked()
    {
        // Get the stock name and quantity from the form
        char *name = get_text_field("stock_name");
        int quantity = atoi(get_text_field("quantity"));
     
        // Call the buy_stock function with the stock name and quantity
        buy_stock(name, quantity);
    }