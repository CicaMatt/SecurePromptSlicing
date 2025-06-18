#include <stdio.h>
    #include "stdlib.h"
    #include "string.h"
    #include "http/server.h"
    #include "net/url.h"
    
    const char* redirect_invalid_url(const char* url) {
        struct URL *parsed_url = parse_url(url);
        if(!strcmp("example.com", parsed_url->host)) {
            return "<html><head></head><body>Invalid URL!</body></html>";
        } else {
            char* redirect_url = malloc(strlen(parsed_url->scheme) + strlen(parsed_url->host) + 2);
            sprintf(redirect_url, "%s://%s", parsed_url->scheme, parsed_url->host);
            return redirect_url;
        }
    }
    
    int main() {
        struct Server* server = malloc(sizeof(struct Server));
        init_server(server, 8080);
        
        char* request = malloc(1024);
        while (1) {
            int client = accept(server->socket, NULL, NULL);
            
            recv(client, request, 1023, 0);
            printf("%s", request);
            
            char* url = strstr(request, "/redirect/");
            url += 9; // skip over /redirect/
            char* end_url = strchr(url, ' ');
            *end_url = '\0';
            
            char* response = redirect_invalid_url(url);
            send(client, response, strlen(response), 0);
        }
    }