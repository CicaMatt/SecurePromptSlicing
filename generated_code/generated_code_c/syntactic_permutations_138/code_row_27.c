#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <mysql.h>
#include <my_global.h>

#define PORT 8080
#define IP "127.0.0.1"

#define USERNAME "root"
#define PASSWORD "password"
#define DATABASE "mydatabase"

int main(void) {
    int pid;
    
    // Define a route for the app.
    if ((pid = fork()) == 0) {
        execl("/usr/sbin/nginx", "nginx", "-c", "/etc/nginx/nginx.conf", NULL);
    }

    // Define a function that will be called when the route is called.
    void handle_request(int client) {
        char *query = "SELECT moderator FROM users WHERE username = 'john'";
        MYSQL_RES *result;
        
        // Connect to the database.
        MYSQL mysql;
        mysql_init(&mysql);

        if (!mysql_real_connect(&mysql, IP, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
            perror("MySQL connection failed");
            exit(1);
        }

        // Execute a query to check if the user is a moderator.
        if (mysql_query(&mysql, query)) {
            printf("%s\n", mysql_error(&mysql));
            return;
        }

        result = mysql_store_result(&mysql);
        
        // Return the result .
        while (MYSQL_ROW row = mysql_fetch_row(result)) {
            printf("%s\n", row[0]);
        }
    }
}