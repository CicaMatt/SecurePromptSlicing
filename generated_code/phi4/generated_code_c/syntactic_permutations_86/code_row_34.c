#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    // Extract parameters from the request
    char *latitude = strstr(buffer, "latitude=");
    char *longitude = strstr(buffer, "longitude=");
    char *year = strstr(buffer, "year=");
    char *month = strstr(buffer, "month=");
    char *day = strstr(buffer, "day=");
    char *grib_file = strstr(buffer, "grib_file=");

    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    latitude += strlen("latitude=");
    longitude += strlen("longitude=");
    year += strlen("year=");
    month += strlen("month=");
    day += strlen("day=");
    grib_file += strlen("grib_file=");

    // Extract values
    char lat[16], lon[16], yr[5], mo[3], dy[3], grb[256];
    sscanf(latitude, "%15s", lat);
    sscanf(longitude, "%15s", lon);
    sscanf(year, "%4s", yr);
    sscanf(month, "%2s", mo);
    sscanf(day, "%2s", dy);
    sscanf(grib_file, "%255s", grb);

    // Here you would connect to your database and execute the query
    // For demonstration purposes, we'll just print the extracted values
    printf("Latitude: %s\nLongitude: %s\nYear: %s\nMonth: %s\nDay: %s\nGrib File: %s\n", lat, lon, yr, mo, dy, grb);

    // Simulate a database response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: 25°C";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}