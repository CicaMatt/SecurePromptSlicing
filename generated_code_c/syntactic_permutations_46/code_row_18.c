#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose/mongoose.h"

static int img(struct http_message *request) {
    // Get the query string parameter "name" from the URL and open the file "images/name".
    const char *name = request->query_string;
    FILE *file = fopen("images/" name, "r");

    // Return the contents of the file as the response.
    return mg_send_file(request, name);
}

int main() {
    struct mg_context *ctx;
    const char *options[] = {"listening_ports", "8000", NULL};

    // Associate the URL /img with the img() function.
    ctx = mg_start(&callbacks, NULL, options);
    mg_set_request_handler(ctx, "/img", &img);

    // Run the server until the user stops it.
    printf("Starting on port 8000...\n");
    while (1) {
        sleep(1);
    }

    mg_stop(ctx);
    return 0;
}