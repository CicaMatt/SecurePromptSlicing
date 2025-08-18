#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#ifdef __linux__
# include <sys/socket.h>
# include <netinet/in.h>
#endif

#include "mongoose.h"

static struct mg_serve_http_opts shttp_server_opts;

void signal_handler(int signum) {
    printf("Caught signal %d\n", signum);
    exit(1);
}

const char *response_html(const char *username, const char *email, const char *last_4_digits) {
    static char response[1024];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>", username, email, last_4_digits);
    return response;
}

void ev_handler(struct mg_connection *nc, int event, void *ev_data) {
    if (event == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        const char *username = "JohnDoe";
        const char *email = "john.doe@example.com";
        const char *last_4_digits = "1234";

        mg_send_head(nc, 200, strlen(response_html(username, email, last_4_digits)), "Content-Type: text/html");
        mg_printf(nc, "%s", response_html(username, email, last_4_digits));
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    shttp_server_opts.document_root = ".";  
    shttp_server_opts.enable_directory_listing = "no";

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "http://localhost:8080", ev_handler);

    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    signal(SIGINT, signal_handler);

    printf("Starting web server on http://localhost:8080\nPress Ctrl-C to exit.\n");

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


To compile and run this code:

1. Install Mongoose library:
   - On Debian-based systems: `sudo apt-get install libmongoose-dev`
   - On Red Hat-based systems: `sudo yum install mongoose-devel`
   - Download source from [Mongoose GitHub](https://github.com/cesanta/mongoose) if not available via package manager.

2. Compile the code:
   
   gcc -o webapp main.c -lmongoclient
   

3. Run the application:
   
   ./webapp
   

4. Access `http://localhost:8080/info` in your browser to see the user information page.