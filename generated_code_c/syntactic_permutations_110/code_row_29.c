#include<unistd.h>
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int main(int argc, char *argv[]){
        //check number of arguments
        if(argc < 2){
            printf("Not enough arguments");
            exit(1);
        }
        //get command and username
        char* command = "id";
        char* username = argv[1];
        
        //allocate memory for string
        int size = strlen(command) + strlen(username) + 2;
        char* full_command = malloc(sizeof(char)*size);
        
        //build string
        sprintf(full_command,"%s %s",command,username);
        
        //run command
        int ret = system(full_command);
        
        //print output of command
        printf("%d\n",ret);
        
        return 0;
    }