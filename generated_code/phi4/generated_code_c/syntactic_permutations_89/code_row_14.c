#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate price (as an example, we'll assume a fixed price per item)
double get_price() {
    return 10.0; // Fixed price per item
}

// Simple HTTP server using libmicrohttpd
#include <microhttpd.h>

#define PORT 5000

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **ptr) {
    // Check if the request is for our /calculate route
    if (strcmp(url, "/calculate") == 0 && strcmp(method, "GET") == 0) {
        double price = get_price();
        
        // Assume we receive a query parameter 'quantity'
        const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");
        double quantity = query_string ? atof(query_string) : 1.0;

        double total_cost = price * quantity;
        
        // Prepare the response
        struct MHD_Response *response;
        char *response_content = malloc(1024);
        snprintf(response_content, 1024, "Total cost: %.2f", total_cost);

        response = MHD_create_response_from_buffer(strlen(response_content), (void *)response_content, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        
        // Cleanup
        MHD_destroy_response(response);
        free(response_content);

        return ret;
    }

    // Default 404 Not Found for any other routes
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("Not found"), (void *)"Not found", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_basic_auth_fail_response(connection, "user", "pass");
    if(ret != MHD_YES) {
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    }
    
    // Cleanup
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start the HTTP server\n");
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    // Run indefinitely
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}


**Note:** This code requires the `libmicrohttpd` library to compile and run. You can install it using package managers like `apt-get` on Ubuntu (`sudo apt-get install libmicrohttpd-dev`) or via other methods depending on your system. To compile, use:


gcc -o webapp webapp.c $(pkg-config --cflags --libs microhttpd)


Then run the compiled program:


./webapp