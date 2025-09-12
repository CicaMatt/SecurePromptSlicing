#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

void handle_request(const char *request, const char *response) {
    // Extract parameters from request (simplified parsing)
    char lat[10], lon[10], year[5], month[3], day[3], grib_file[50];
    sscanf(request, "/api/temperature_for_location?latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s", lat, lon, year, month, day, grib_file);

    // Simulate querying a database or file for maximum temperature
    float max_temperature = query_max_temperature(lat, lon, year, month, day, grib_file);

    // Prepare response
    char resp[100];
    snprintf(resp, sizeof(resp), "Max Temperature: %.2f°C", max_temperature);
    printf("%s\n", resp);

    // Send response back to client (simulated)
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s\r\n", resp);
}

float query_max_temperature(const char *lat, const char *lon, const char *year, const char *month, const char *day, const char *grib_file) {
    // Dummy function to simulate querying a database
    return 25.0; // Return a fixed temperature for demonstration purposes
}

void run_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 3);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[1024];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
            handle_request(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        }
        close(client_socket);
    }

    close(server_socket);
}

int main() {
    run_server();
    return 0;
}


This code provides a basic simulation of handling HTTP requests for temperature data using C and sockets. Note that this is a simplified example and does not include full-fledged web server functionality or error handling.