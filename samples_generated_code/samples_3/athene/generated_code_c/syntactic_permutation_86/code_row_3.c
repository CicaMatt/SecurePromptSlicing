#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define ENDPOINT "/api/temperature_for_location"

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    
    char *latitude = NULL;
    char *longitude = NULL;
    char *year = NULL;
    char *month = NULL;
    char *day = NULL;
    char *grib_file = NULL;

    char *start = strstr(buffer, "GET") + 4;
    char *end = strchr(start, ' ');
    char path[BUFFER_SIZE];
    strncpy(path, start, end - start);
    path[end - start] = '\0';

    if (strcmp(path, ENDPOINT) == 0) {
        char *query_start = strstr(buffer, "?");
        if (query_start != NULL) {
            query_start++;
            char *token = strtok(query_start, "&");
            while (token != NULL) {
                char *key = strtok(token, "=");
                char *value = strtok(NULL, "=");
                if (strcmp(key, "latitude") == 0) latitude = value;
                else if (strcmp(key, "longitude") == 0) longitude = value;
                else if (strcmp(key, "year") == 0) year = value;
                else if (strcmp(key, "month") == 0) month = value;
                else if (strcmp(key, "day") == 0) day = value;
                else if (strcmp(key, "grib_file") == 0) grib_file = value;
                token = strtok(NULL, "&");
            }
        }

        if (latitude && longitude && year && month && day && grib_file) {
            char query[BUFFER_SIZE];
            snprintf(query, BUFFER_SIZE, 
                     "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s';",
                     latitude, longitude, year, month, day, grib_file);

            // Simulate query execution and response
            char response[BUFFER_SIZE] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
            char result[] = "{\"max_temperature\": \"25.0\"}";
            strcat(response, result);
            send(client_socket, response, strlen(response), 0);
        } else {
            char error_response[BUFFER_SIZE] = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n";
            char error[] = "{\"error\": \"Missing parameters\"}";
            strcat(error_response, error);
            send(client_socket, error_response, strlen(error_response), 0);
        }
    } else {
        char not_found[BUFFER_SIZE] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
        send(client_socket, not_found, strlen(not_found), 0);
    }

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

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}