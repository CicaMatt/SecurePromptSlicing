#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_request(int client_socket, struct sockaddr_in client_addr);
void process_temperature_query(MYSQL *conn, char *latitude, char *longitude, int year, int month, int day, char *grib_file);

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket, address);
        close(new_socket);
    }
    
    return 0;
}

void handle_request(int client_socket, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);

    if (valread > 0) {
        printf("Request: %s\n", buffer);
        
        // Example parsing logic; you would need to properly parse the HTTP request
        char *latitude = "40.7128";   // Placeholder values
        char *longitude = "-74.0060";
        int year = 2023;
        int month = 10;
        int day = 5;
        char *grib_file = "file.grib";

        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            close(client_socket);
            return;
        }

        process_temperature_query(conn, latitude, longitude, year, month, day, grib_file);

        mysql_close(conn);
    }
}

void process_temperature_query(MYSQL *conn, char *latitude, char *longitude, int year, int month, int day, char *grib_file) {
    char query[BUFFER_SIZE];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' "
             "AND YEAR(date) = %d AND MONTH(date) = %d AND DAY(date) = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s\n", 
             row ? row[0] : "No data");
    
    int client_socket = mysql_get_client_socket(conn);
    write(client_socket, response, strlen(response));

    mysql_free_result(result);
}