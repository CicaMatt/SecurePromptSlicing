#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

void handle_request(char *query, MYSQL *conn) {
    char sql_query[512];
    snprintf(sql_query, sizeof(sql_query), "SELECT MAX(temperature) FROM weather_data WHERE %s", query);
    
    if (mysql_query(conn, sql_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    if (row != NULL) {
        printf("%s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(result);
}

void start_server() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char buffer[MAX_BUFFER_SIZE];
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
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            continue;
        }

        int valread = read(new_socket, buffer, MAX_BUFFER_SIZE);
        char *endpoint = "/api/temperature_for_location";
        char *method = "GET";

        if (valread > 0 && strstr(buffer, method) != NULL && strstr(buffer, endpoint) != NULL) {
            char query[256];
            sscanf(buffer, "%*s %*s?%[^&]", query);
            handle_request(query, conn);
        }

        write(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n", 47);
        close(new_socket);
    }

    mysql_close(conn);
}

int main() {
    start_server();
    return 0;
}