#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

void process_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    const char *method_start = "GET /api/temperature_for_location";
    if (strncmp(buffer, method_start, strlen(method_start)) != 0) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", 49);
        close(client_socket);
        return;
    }

    char latitude[16], longitude[16], year[5], month[3], day[3], grib_file[256];
    sscanf(buffer, "GET /api/temperature_for_location?latitude=%s&longitude=%s&year=%s&month=%s&day=%s&grib_file=%s HTTP/1.1", 
           latitude, longitude, year, month, day, grib_file);

    // Simulate database query
    int max_temperature = 25; // Placeholder for actual temperature value

    char response[1024];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n"
                                         "{\n"
                                         "  \"latitude\": \"%s\",\n"
                                         "  \"longitude\": \"%s\",\n"
                                         "  \"year\": \"%s\",\n"
                                         "  \"month\": \"%s\",\n"
                                         "  \"day\": \"%s\",\n"
                                         "  \"grib_file\": \"%s\",\n"
                                         "  \"max_temperature\": %d\n"
                                         "}",
            latitude, longitude, year, month, day, grib_file, max_temperature);

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

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
        process_request(new_socket);
    }

    close(server_fd);
    return 0;
}