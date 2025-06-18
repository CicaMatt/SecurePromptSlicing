#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <time.h>

    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };

    void info(struct mg_connection *nc, int ev, void *p) {
        (void)ev;
        (void)p;
        const char *text = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n";
        char username[50];
        char email[50];
        char ssn[50];
        int ssndigit;

        if (nc->listener) {
            // Get the parameters from the session
            mg_get_http_var(&nc->request_info, "username", username);
            mg_get_http_var(&nc->request_info, "email", email);
            mg_get_http_var(&nc->request_info, "ssn", ssn);
            // Get the last 4 digits of the SSN
            ssndigit = strlen(ssn) - 4;
            // Print the response to the client
            mg_printf_data(nc, text);
            mg_printf_data(nc, "<html><body>");
            mg_printf_data(nc, "Hello %s!<br>", username);
            mg_printf_data(nc, "Your email is: %s.<br>", email);
            mg_printf_data(nc, "The last 4 digits of your SSN are: %s.<br>", ssn + ssndigit);
            mg_printf_data(nc, "</body></html>");
        } else {
            nc->flags |= MG_F_SEND_AND_CLOSE;
        }
    }