#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <openssl/ssl.h>
    #include <openssl/err.h>
    
    #define PORT 8080
    #define BUF_SIZE 4096
    
    // SSL initialization
    static int init_ssl(void){
        SSL_library_init();
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();
        return 0;
    }
    
    // Create a socket and bind it to a port
    static int create_socket(void){
        int server_fd, new_socket;
        struct addrinfo hints, *serv_addr, *p;
        int status;
        char ipstr[INET6_ADDRSTRLEN];
    
        // Get the address info
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
    
        if((status = getaddrinfo(NULL, PORT, &hints, &serv_addr)) != 0){
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            return -1;
        }
    
        // Loop through the results and bind to the first one that works
        for(p = serv_addr; p != NULL; p = p->ai_next){
            if((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) continue;
    
            if(bind(server_fd, p->ai_addr, p->ai_addrlen) == -1){
                close(server_fd);
                continue;
            }
            break;
        }
    
        if(p == NULL){
            fprintf(stderr, "failed to bind socket\n");
            return -2;
        }
    
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr*) p->ai_addr), ipstr, sizeof(ipstr));
        printf("server on address %s\n", ipstr);
    
        freeaddrinfo(serv_addr);
    
        if(listen(server_fd, 3) == -1){
            perror("listen");
            return -3;
        }
    
        return server_fd;
    }
    
    // Handle a new client connection
    static void handle_client(int client_fd){
        char buffer[BUF_SIZE];
        int read_size, write_size;
        SSL *ssl = NULL;
    
        // Read the request from the client
        bzero(buffer, BUF_SIZE);
        read_size = recv(client_fd, buffer, BUF_SIZE-1, 0);
        if(read_size < 0){
            fprintf(stderr, "failed to read from socket\n");
            goto done;
        }
    
        // Print the request
        printf("request: %s", buffer);
    
        // Send a response back to the client
        char *message = "Hello, client";
        write_size = send(client_fd, message, strlen(message), 0);
        if(write_size < 0){
            fprintf(stderr, "failed to write to socket\n");
            goto done;
        }
    
    done:
        close(client_fd);
        SSL_free(ssl);
        return;
    }
    
    // Get the IP address as a string
    static void *get_in_addr(struct sockaddr *sa){
        if(sa->sa_family == AF_INET) return &(((struct sockaddr_in*) sa)->sin_addr);
        return &(((struct sockaddr_in6*) sa)->sin6_addr);
    }
    
    int main(void){
        SSL_CTX *ctx;
        int server_fd, client_fd;
        struct addrinfo hints, *serv_addr, *p;
        socklen_t client_size;
        struct sockaddr_storage client_addr;
    
        // Initialize SSL
        init_ssl();
    
        // Create a new context using TLS 1.2
        ctx = SSL_CTX_new(TLSv1_2_server_method());
        if(!ctx){
            fprintf(stderr, "failed to create SSL context\n");
            return -1;
        }
    
        // Set the key and certificate for the server
        if(SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) < 0){
            ERR_print_errors_fp(stderr);
            return -2;
        }
    
        // Load the private key into the context
        if(SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) < 0){
            ERR_print_errors_fp(stderr);
            return -3;
        }
    
        // Check that the certificate and private key match
        if(!SSL_CTX_check_private_key(ctx)){
            fprintf(stderr, "certificate and private key do not match\n");
            return -4;
        }
    
        // Create a new socket and bind it to a port
        server_fd = create_socket();
        if(server_fd < 0){
            fprintf(stderr, "failed to create/bind socket\n");
            return -5;
        }
    
        while(1){
            // Accept a new client connection
            client_size = sizeof(client_addr);
            client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &client_size);
            if(client_fd < 0){
                perror("accept");
                continue;
            }
    
            // Handle the new connection in a new thread
            handle_client(client_fd);
        }
    
        return 0;
    }