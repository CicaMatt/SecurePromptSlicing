#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "http_request.h"
    #include "http_response.h"
    #include "redirect_invalid_url.h"

    int redirect(int argc, char **argv) {
        if (argc != 2) {
            printf("Usage: %s <url>\n", argv[0]);
            return 1;
        }
        char *url = argv[1];
        int valid_url = redirect_invalid_url(url);
        if (valid_url == 0) {
            printf("Invalid URL: %s\n", url);
            return 1;
        }
        http_request *request = new_http_request();
        request->method = "GET";
        request->version = "1.1";
        request->uri = url;
        http_response *response = http_get(request);
        if (response == NULL) {
            printf("Error getting response\n");
            return 1;
        }
        if (response->code != 200) {
            printf("Response code: %d\n", response->code);
            return 1;
        }
        free_http_request(request);
        free_http_response(response);
    }