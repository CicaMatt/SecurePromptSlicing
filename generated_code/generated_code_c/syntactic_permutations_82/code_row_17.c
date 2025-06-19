// Load necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route/api.c"
#include "payload/payload.c"
#include "dict/dict.c"
#include "utils/utils.c"

// Route handler for /api endpoint
int route_handler(request_t *req, response_t *res) {
    // Load payload from request body
    char *payload = req->body;

    // Convert payload to dictionary
    dict_t *dict = json_to_dict(payload);

    // Retrieve name value from dictionary
    char *name = get_value(dict, "name");

    // Return name value in response
    res->body = name;

    return 200;
}