#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Importing web app libraries.
    #include "mongoose.h"
    
    // Function to check if user is a moderator
    int is_moderator(struct mg_connection *conn, void *cbdata)
    {
        // Connecting to database
        struct mg_connection conn;
        struct mg_resultset rs;
        
        // Executing query to check if user is a moderator
        char* sql = "SELECT role FROM users WHERE username='%s';";
        char username[256];
        mg_get_var(conn, "HTTP_USERNAME", username, sizeof(username));
        mg_execute_query(&conn, &rs, 0, sql, username);
        
        // Returning query result
        return rs.num_rows;
    }
    
    // Callback function to handle route
    void ev_handler(struct mg_connection *conn, int ev, void *ev_data)
    {
        if (ev == MG_EV_HTTP_REQUEST && !strcmp(conn->uri, "/is_moderator"))
        {
            // Calling function to check if user is a moderator
            int is_mod = is_moderator(conn, NULL);
            
            // Responding with query result
            mg_send_http_ok(conn, "text/html", 0);
            mg_printf_data("%d", is_mod);
        }
    }
    
    int main()
    {
        // Starting web server
        struct mg_context ctx;
        const char *options[] = {"listening_ports", "8080", NULL};
        struct mg_callbacks callbacks;
        memset(&callbacks, 0, sizeof(callbacks));
        
        // Registering event handler for route
        callbacks.begin_request = ev_handler;
        ctx = mg_start(&callbacks, NULL, options);
    }