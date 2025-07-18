#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sqlite3.h> 

#define PORT 9001 
#define BACKLOG 5 

int main() { 
    char email[256]; 
    const char *db_path = "./mailing_list.db"; 
    sqlite3 *db; 
    int rc, i, c, opt = 1; 
    struct sockaddr_in server; 
    socklen_t addrlen = sizeof(server); 
    int sockfd, newsockfd; 

    // create the database if it does not exist yet 
    rc = sqlite3_open(db_path, &db); 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } else { 
        printf("Database opened successfully\n"); 
    } 

    // create the database table if it does not exist yet 
    char *sql = "CREATE TABLE IF NOT EXISTS mailing_list (email TEXT PRIMARY KEY);"; 
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL); 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 

    // start the socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0) { 
        perror("Socket creation failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("Socket created successfully\n"); 
    } 

    // set socket options 
    rc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); 
    if (rc < 0) { 
        perror("setsockopt() failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("Socket options set successfully\n"); 
    } 

    // bind the socket to an address and port number 
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT); 
    rc = bind(sockfd, (struct sockaddr *)&server, addrlen); 
    if (rc < 0) { 
        perror("bind() failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("Server socket bound successfully\n"); 
    } 

    // start listening on the port 
    rc = listen(sockfd, BACKLOG); 
    if (rc < 0) { 
        perror("listen() failed"); 
        exit(EXIT_FAILURE); 
    } else { 
        printf("Server socket listening successfully\n"); 
    } 

    // accept incoming connections and process them in a loop 
    while (1) { 
        newsockfd = accept(sockfd, (struct sockaddr *)&server, &addrlen); 
        if (newsockfd < 0) { 
            perror("accept() failed"); 
            exit(EXIT_FAILURE); 
        } else { 
            printf("Accepted incoming connection\n"); 
        } 

        // handle the GET request 
        char buffer[256]; 
        bzero(buffer, sizeof(buffer)); 
        read(newsockfd, buffer, 255); 
        printf("%s", buffer); 
        char *token = strtok(buffer, " "); 
        if (strcmp(token, "GET") == 0) { 
            token = strtok(NULL, " "); 
            if (strcmp(token, "/unsubscribe") == 0) { 
                // extract email from query string 
                char *query = strtok(NULL, "&"); 
                char *email_param = strtok(query, "="); 
                char *email_value = strtok(NULL, "="); 
                if (strcmp(email_param, "email") == 0) { 
                    // delete user from database 
                    char *sql = "DELETE FROM mailing_list WHERE email = ?;"; 
                    rc = sqlite3_exec(db, sql, NULL, NULL, NULL); 
                    if (rc != SQLITE_OK) { 
                        fprintf(stderr, "Failed to delete user: %s\n", sqlite3_errmsg(db)); 
                        sqlite3_close(db); 
                        return 1; 
                    } else { 
                        printf("User deleted successfully from database\n"); 
                    } 
                    // unsubscribe user from mailing list 
                    char *sql = "UPDATE mailing_list SET subscribed = ? WHERE email = ?;"; 
                    rc = sqlite3_exec(db, sql, NULL, NULL, NULL); 
                    if (rc != SQLITE_OK) { 
                        fprintf(stderr, "Failed to unsubscribe user: %s\n", sqlite3_errmsg(db)); 
                        sqlite3_close(db); 
                        return 1; 
                    } else { 
                        printf("User unsubscribed successfully from mailing list\n"); 
                    } 
                } 
            } 
        } 

        // close the socket and connection with the client 
        rc = shutdown(newsockfd, SHUT_RDWR); 
        if (rc < 0) { 
            perror("shutdown() failed"); 
            exit(EXIT_FAILURE); 
        } else { 
            printf("Socket and connection with client closed successfully\n"); 
        } 
    } 
}