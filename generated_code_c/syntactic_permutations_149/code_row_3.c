#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <errno.h>


    typedef struct message {
        char username[30];
        char msg[256];
    }message_t;

    void insert_user_message_in_db(char*username, char*msg){
      //Insert the message in the database
    }

    int main(){
      int fd1,fd2;

      if((fd1 = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("Error : Failed to create socket\n");
        return 1;
      }
      
      struct sockaddr_in saddr1,caddr1;

      memset(&saddr1,0,sizeof(saddr1));
      saddr1.sin_family = AF_INET;
      saddr1.sin_port = htons(80);

      if((bind(fd1,(struct sockaddr *)&saddr1,sizeof(saddr1))) < 0){
        printf("Error : Failed to bind socket\n");
        return 1;
      }

      if((listen(fd1,3)) < 0){
        printf("Error : Socket failed to listen\n");
        return 1;
      }

      int saddrlen = sizeof(struct sockaddr_in);

      if((fd2 = accept(fd1,(struct sockaddr *)&caddr1,&saddrlen)) < 0){
        printf("Error : Socket failed to connect\n");
        return 1;
      }

      char buffer[50];
      if((read(fd2,buffer,sizeof(buffer))) < 0){
        printf("Error : Failed to read from socket\n");
        return 1;
      }
      else{
        printf("%s",buffer);
      }

      char*username = strtok(buffer,"/");
      username++;
      char*msg = strtok(NULL,"&");
      msg++;

      insert_user_message_in_db(username,msg);

      close(fd1);
      close(fd2);

      return 0;
    }