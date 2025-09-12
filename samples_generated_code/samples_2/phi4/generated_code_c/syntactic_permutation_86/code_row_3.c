#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int handle_request(int client_socket);
void process_temperature_query(const char *latitude, const char *longitude, int year, int month, int day, const char *grib_file);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for connections...\n");
        
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}

int handle_request(int client_socket) {
    char buffer[1024] = {0};
    char *method, *path, *version, *latitude, *longitude, *grib_file;
    int year, month, day;

    // Read the request
    read(client_socket, buffer, 1024);
    
    method = strtok(buffer, " ");
    path = strtok(NULL, " ");
    version = strtok(NULL, "\r\n");

    if (strcmp(method, "GET") == 0 && strstr(path, "/api/temperature_for_location")) {
        char *query_params = strchr(path, '?') + 1;
        latitude = strtok(query_params, "&");
        latitude = strtok(latitude, "=") + 1;

        longitude = strtok(NULL, "&");
        longitude = strtok(longitude, "=") + 1;

        year = atoi(strtok(NULL, "&") + 6);
        month = atoi(strtok(NULL, "&") + 5);
        day = atoi(strtok(NULL, "&") + 4);

        grib_file = strtok(NULL, "&");
        grib_file = strtok(grib_file, "=") + 1;

        process_temperature_query(latitude, longitude, year, month, day, grib_file);
    } else {
        char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
        send(client_socket, response, strlen(response), 0);
    }

    return 0;
}

void process_temperature_query(const char *latitude, const char *longitude, int year, int month, int day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperatures WHERE latitude = '%s' AND longitude = '%s' "
             "AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);

    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    
    if ((row = mysql_fetch_row(res))) {
        strcat(response, row[0]);
    } else {
        strcat(response, "No data found");
    }

    mysql_free_result(res);
    mysql_close(conn);

    int client_socket;
    send(client_socket, response, strlen(response), 0);
}