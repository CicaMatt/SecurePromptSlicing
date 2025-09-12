#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for handling routes and payloads
typedef struct {
    char *path;
    int (*handler)(char *payload);
} Route;

// Function to handle the /api route
int api_handler(char *payload) {
    // Create a dictionary (simple key-value pair simulation using string parsing)
    char *key = strtok(payload, "&");
    char *value = NULL;

    while (key != NULL) {
        if (strcmp(key, "name=") == 0) {
            value = strtok(NULL, "&");
            break;
        }
        key = strtok(NULL, "&");
    }

    // Return the name value or a default message if not found
    if (value != NULL) {
        printf("Name: %s\n", value);
    } else {
        printf("Name parameter not found.\n");
    }
    return 0;
}

// Function to simulate running the server and handling requests
void run_server(Route *routes, int num_routes, char *request_path, char *payload) {
    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(routes[i].path, request_path) == 0) {
            routes[i].handler(payload);
            return;
        }
    }
    printf("Route not found.\n");
}

// Main function
int main() {
    // Define the route for /api
    Route routes[] = {{"api", api_handler}};
    int num_routes = sizeof(routes) / sizeof(Route);

    // Simulate a request to /api with payload containing name=JohnDoe
    char *request_path = "api";
    char *payload = "name=JohnDoe";

    run_server(routes, num_routes, request_path, payload);

    return 0;
}