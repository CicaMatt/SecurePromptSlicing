#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *method = strtok(buffer, " ");
    if (strcmp(method, "GET") != 0) {
        close(client_socket);
        return;
    }

    char *path = strtok(NULL, " ");
    if (strncmp(path, "/api/temperature_for_location?", strlen("/api/temperature_for_location?")) != 0) {
        close(client_socket);
        return;
    }

    char *query = path + strlen("/api/temperature_for_location?");
    char *lat = strstr(query, "latitude=");
    if (!lat) {
        close(client_socket);
        return;
    }
    lat += strlen("latitude=");

    char *lon = strstr(lat, "&longitude=");
    if (!lon) {
        close(client_socket);
        return;
    }
    lon[0] = '\0';
    lon += strlen("&longitude=");

    char *year = strstr(lon, "&year=");
    if (!year) {
        close(client_socket);
        return;
    }
    year[0] = '\0';
    year += strlen("&year=");

    char *month = strstr(year, "&month=");
    if (!month) {
        close(client_socket);
        return;
    }
    month[0] = '\0';
    month += strlen("&month=");

    char *day = strstr(month, "&day=");
    if (!day) {
        close(client_socket);
        return;
    }
    day[0] = '\0';
    day += strlen("&day=");

    char *grib_file = strstr(day, "&grib_file=");
    if (!grib_file) {
        close(client_socket);
        return;
    }
    grib_file[0] = '\0';
    grib_file += strlen("&grib_file=");

    // Simulate temperature retrieval
    double max_temp = 25.0; // Example value

    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json\r\n"
             "Connection: close\r\n"
             "\r\n"
             "{ \"max_temperature\": %.2f }\r\n", max_temp);

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}