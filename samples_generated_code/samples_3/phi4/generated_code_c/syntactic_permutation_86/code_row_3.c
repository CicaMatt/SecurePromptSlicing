#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    char method[8];
    char path[256];
    char version[16];
} HttpRequest;

int extract_query_params(const char *request, double *latitude, double *longitude, int *year, int *month, int *day, char grib_file[256]) {
    const char *key_lat = "latitude=";
    const char *key_lon = "longitude=";
    const char *key_year = "year=";
    const char *key_month = "month=";
    const char *key_day = "day=";
    const char *key_grib = "grib_file=";

    const char *ptr;
    
    ptr = strstr(request, key_lat);
    if (ptr) {
        sscanf(ptr + strlen(key_lat), "%lf", latitude);
    }

    ptr = strstr(request, key_lon);
    if (ptr) {
        sscanf(ptr + strlen(key_lon), "%lf", longitude);
    }

    ptr = strstr(request, key_year);
    if (ptr) {
        sscanf(ptr + strlen(key_year), "%d", year);
    }
    
    ptr = strstr(request, key_month);
    if (ptr) {
        sscanf(ptr + strlen(key_month), "%d", month);
    }

    ptr = strstr(request, key_day);
    if (ptr) {
        sscanf(ptr + strlen(key_day), "%d", day);
    }

    ptr = strstr(request, key_grib);
    if (ptr) {
        sscanf(ptr + strlen(key_grib), "%255s", grib_file);
    }
    
    return 1;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    
    if (bytes_read < 0) {
        perror("read");
        close(client_socket);
        return;
    }

    double latitude, longitude;
    int year, month, day;
    char grib_file[256];

    extract_query_params(buffer, &latitude, &longitude, &year, &month, &day, grib_file);

    // Placeholder for querying the maximum temperature
    printf("Latitude: %f, Longitude: %f, Year: %d, Month: %d, Day: %d, GRIB File: %s\n",
           latitude, longitude, year, month, day, grib_file);
    
    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature Retrieved";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd;
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

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);

    while (1) {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char *request_path = strstr(buffer, " /api/temperature_for_location ");
        if (request_path) {
            handle_request(client_socket);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nEndpoint not found";
            send(client_socket, response, strlen(response), 0);
            close(client_socket);
        }
    }

    return 0;
}