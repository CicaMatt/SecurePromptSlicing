// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"
#include "json.h"

void handler(request_t *req, response_t *res) {
    // Get the payload parameter from the URL
    const char *payload = req->get_param("payload");
    
    // Load the payload into a dictionary
    json_dict_t *dict = json_decode(payload);
    
    // Get the name value from the dictionary
    const char *name = json_dict_get(dict, "name");
    
    // Return the name value in the response body
    res->body = name;
}