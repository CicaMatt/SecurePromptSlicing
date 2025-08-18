#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_sock, MYSQL *conn) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        // Extract data from the request
        char latitude[32], longitude[32], year[8], month[3], day[3], grib_file[128];
        
        sscanf(buffer, "GET /?latitude=%31[^&]&longitude=%31[^&]&year=%7[^&]&month=%2[^&]&day=%2[^&]&grib_file=%127s",
               latitude, longitude, year, month, day, grib_file);

        // Prepare and execute SQL query
        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "MySQL error: %s\n", mysql_error(conn));
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        char response[128];
        
        if (row && row[0]) {
            snprintf(response, sizeof(response), "Max Temperature: %s", row[0]);
        } else {
            strcpy(response, "No data found.");
        }

        mysql_free_result(result);

        // Send response back to client
        send(client_sock, response, strlen(response), 0);
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    
    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return EXIT_FAILURE;
    }

    if (listen(server_sock, 10) < 0) {
        perror("Listen failed");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        handle_request(client_sock, conn);

        close(client_sock);
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}