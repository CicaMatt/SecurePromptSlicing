#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <mysql.h>
    
    #define PORT 8000
    
    void *get_in_addr(struct sockaddr *sa)
    {
        if (sa->sa_family == AF_INET)
        {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }
        
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
    
    int main()
    {
        int sockfd, newsockfd;
        char buffer[1024];
        struct addrinfo hints, *servinfo, *p;
        socklen_t clilen;
        struct sockaddr_storage cli_addr;
        
        // create socket and get address information
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        
        if ((getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
        {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(errno));
            return 1;
        }
        
        // bind socket and listen for connection requests
        for (p = servinfo; p != NULL; p = p->ai_next)
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {
                perror("server: socket");
                continue;
            }
            
            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
                close(sockfd);
                perror("server: bind");
                continue;
            }
            
            break;
        }
        
        freeaddrinfo(servinfo);
        
        if (p == NULL)
        {
            fprintf(stderr, "server: failed to bind\n");
            return 2;
        }
        
        if (listen(sockfd, 10) == -1)
        {
            perror("listen");
            exit(1);
        }
        
        printf("Waiting for connections...\n");
        
        // wait for connection request and accept it
        while (1)
        {
            clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
            
            if (newsockfd < 0)
                perror("accept");
            
            // send a message to the connected client
            char *message = "You have been successfully connected\n";
            write(newsockfd, message, strlen(message));
            
            // read data from the connected client and print it out
            memset(buffer, 0, sizeof(buffer));
            int n = read(newsockfd, buffer, 1024);
            
            if (n < 0)
                perror("read");
            
            printf("%s\n", buffer);
            close(newsockfd);
        }
        
        return 0;
    }