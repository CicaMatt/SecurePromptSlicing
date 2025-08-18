#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
    float latitude;
    float longitude;
    int year;
    int month;
    int day;
    char grib_file[256];
} QueryParams;

void parse_request(const char *request, QueryParams *params) {
    sscanf(request, "/api/temperature_for_location?latitude=%f&longitude=%f&year=%d&month=%d&day=%d&grib_file=%s",
           &params->latitude, &params->longitude, &params->year, &params->month, &params->day, params->grib_file);
}

float get_max_temperature(QueryParams *params) {
    // Dummy function to simulate database query
    float max_temp = 25.0; // Example value
    return max_temp;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    
    QueryParams params;
    parse_request(buffer, &params);

    float max_temp = get_max_temperature(&params);

    char response[256];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": %.2f}", max_temp);
    
    write(client_socket, response, strlen(response));
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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}