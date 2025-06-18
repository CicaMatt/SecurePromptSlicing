#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mongoose.h"
 
// Create web server structure
struct mg_serve_http_opts s_http_server;

// Struct to store session data
struct user_session {
    char *username;
    int SSN;
};

// Function to generate page with username and last 4 digits of SSN
char* info(int SSN, char *username) {
    // Create string to hold the generated HTML
    char *html = (char*)calloc(8092, sizeof(char));
    
    // Add HTML header
    sprintf(html, "<html><head></head><body>");
    
    // Add username and last 4 digits of SSN
    sprintf(html, "Hello %s! Your last 4 digits of your SSN are %i</body></html>", username, SSN);
    
    return html;
}

// Function to handle route requests
void ev_handler(struct mg_connection *nc, int event, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    struct user_session *session = nc->user_data;
    
    switch(event){
        case MG_EV_HTTP_REQUEST:
            if(!mg_vcmp(&hm->uri, "/info")) {
                mg_send_head(nc, 200, -1, "Content-Type: text/html");
                mg_printf(nc, "%s", info(session->SSN, session->username));
            } else{
                mg_http_send_error(nc, 404, "Not found");
            }
        default:
            break;
    }
}

int main() {
    // Initialize web server options to default values
    memset(&s_http_server, 0, sizeof(s_http_server));
    
    // Set callback function to handle route requests
    s_http_server.document_root = ".";
    s_http_server.request_handler = ev_handler;
    
    // Start web server
    struct mg_context *ctx;
    ctx = mg_start(&s_http_server);
}