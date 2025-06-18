#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "routes.h"

//Create a web app.
int main(int argc, char *argv[]) {
    // Define a route for the app.
    Route *route = malloc(sizeof(Route));
    route->path = "/api/v1/moderator";
    route->function = check_moderator;

    // Define a function that will be called when is called.
    int check_moderator() {
        //Connect to the database.
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "root", "", "mydb", 0, NULL, 0)) {
            printf("Error connecting to database:%s\n", mysql_error(conn));
            return 1;
        }
        //Execute a query to check if the user is a moderator.
        char *query = "SELECT * FROM users WHERE moderator=1";
        MYSQL_RES *result = mysql_store_result(mysql_query(conn, query));
        int num_rows = mysql_num_rows(result);

        //Return the result of the query.
        if (num_rows > 0) {
            printf("Moderator found\n");
            return 1;
        } else {
            printf("No moderators found\n");
            return 0;
        }
    }
}