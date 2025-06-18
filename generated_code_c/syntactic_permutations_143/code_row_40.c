#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include "mysql_connection.h"
    #include "mysql_driver.h"
    #include "mysql_error.h"
    #include "cppconn_exception.h"
    #include "cppconn_resultset.h"
    using namespace sql;

    int main()
    {
        char email[50];
        printf("Enter your email: ");
        gets(email);

        Driver* driver = get_driver_instance();
        Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        Statement* stmt = con->createStatement();
        ResultSet* result;
        char query[500];
        sprintf(query, "DELETE FROM users WHERE email='%s'", email);
        result = stmt->executeQuery(query);
        if (result->next())
        {
            printf("You have been unsubscribed from our mailing list");
        }
        else
        {
            printf("You are not subscribed to our mailing list");
        }
    }