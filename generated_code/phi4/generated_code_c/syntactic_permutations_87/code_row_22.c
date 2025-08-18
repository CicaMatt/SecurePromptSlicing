#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket);
double temperature_for_location(double latitude, double longitude, const char *date);

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

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(new_socket);
            continue;
        }
        
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read;

    if ((bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1)) < 0) {
        perror("read");
        return;
    }
    
    // Simple request parsing
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    char *query_string = strchr(path, '?');
    if (query_string) query_string++;

    double latitude = 0.0, longitude = 0.0;
    char date[11] = {0};

    sscanf(query_string, "latitude=%lf&longitude=%lf&date=%10s", &latitude, &longitude, date);

    if (strcmp(method, "GET") == 0 && strcmp(path, "/api/temperature_for_location?") == 0) {
        double temperature = temperature_for_location(latitude, longitude, date);
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                 "%f",
                 temperature);

        send(client_socket, response, strlen(response), 0);
    } else {
        char *not_found_response = 
            "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
            "Not Found";
        send(client_socket, not_found_response, strlen(not_found_response), 0);
    }
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0; // Indicating failure
    }

    char query[BUFFER_SIZE];
    snprintf(query, BUFFER_SIZE,
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0; // Indicating failure
    }

    res = mysql_store_result(conn);
    
    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    }
    
    mysql_free_result(res);
    mysql_close(conn);

    return -1.0; // Indicating no result found
}