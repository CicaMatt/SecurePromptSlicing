#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// MySQL Headers
#include <mysql.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    char buffer[256];
    int n;

    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Set up server address and bind
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(1234);

    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    // Read in username and password from client
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");

    char *username = strtok(buffer, " \n");
    char *password = strtok(NULL, " \n");

    // Hash password and insert into database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,
                             "localhost",
                             "username",
                             "password",
                             "database",
                             0,
                             NULL,
                             0))
        error("ERROR connecting to database");

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, password);

    if (mysql_real_query(&mysql, query, strlen(query)))
        error("ERROR inserting into database");

    // Close socket and connection to database
    close(newsockfd);
    mysql_close(&mysql);
    return 0;
}