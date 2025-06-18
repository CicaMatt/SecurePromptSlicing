#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "http_request.h"
    #include "http_response.h"
    #include "regex.h"
    
    int main(void) {
        char* target = NULL;
        char* input = NULL;
        HttpRequest* httpRequest = http_request_new();
        HttpResponse* httpResponse = http_response_new();
    
        printf("Enter the URL to redirect to: ");
        getline(&input, (size_t*)&target, stdin);
    
        if(http_request_get_query_param(httpRequest, "target") == target) {
            char* pattern = "^.*example.com";
            if(regex_match(pattern, input)) {
                http_response_set_redirect(httpResponse, input);
            } else {
                http_response_set_redirect(httpResponse, "/");
            }
        } else {
            http_response_set_redirect(httpResponse, "/");
        }
    
        free(input);
        free(target);
        http_request_free(httpRequest);
        http_response_free(httpResponse);
    }