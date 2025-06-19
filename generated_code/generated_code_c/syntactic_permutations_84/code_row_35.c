#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    
    #define BUFFER_SIZE 2048
    #define PORT 5000
    #define LENGTH 16
    
    struct sockaddr_in getSocketInfo(){
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        
        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
    
        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
    
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );
        
        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        
        if (listen(server_fd, 3) < 0){
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        struct sockaddr_in socketInfo;
        char buffer[BUFFER_SIZE];
        memset(&socketInfo, 0, sizeof(socketInfo));
        int messageSize = recvfrom(new_socket, (char *)buffer, BUFFER_SIZE, MSG_PEEK, ( struct sockaddr*) &socketInfo, &addrlen);
        
        return socketInfo;
    }
    
    char* getPayload(struct sockaddr_in *socketInfo){
        int server_fd = 0, new_socket = 0;
        char buffer[BUFFER_SIZE];
        struct sockaddr_in address;
        
        //read the message from client and copy it in buffer
        recvfrom(new_socket , (char *)buffer , BUFFER_SIZE ,  MSG_WAITALL ,(struct sockaddr*) &address, &addrlen);
        printf("Here is the message: %s\n",buffer );
        
        //parsing payload from buffer
        char *payload = strstr(buffer, "payload=");
        if(!payload){
            return NULL;
        }
        int length = LENGTH + 2048;
        char *json = malloc(length);
        memcpy(json, payload, length);
        
        //check if the type is
        char *type = strstr(buffer, "type=yaml");
        if(!type){
            return NULL;
        }
        return json;
    }
    
    int main(){
        struct sockaddr_in socketInfo = getSocketInfo();
        
        //check if the payload is present
        char *payload = getPayload(&socketInfo);
        if(!payload){
            printf("Bad Request: No Payload\n");
        }else{
            printf("Here is the payload: %s\n", payload);
        }
        
        return 0;
    }