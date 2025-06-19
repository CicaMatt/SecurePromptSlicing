#include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>

    char* getUsername();
    void printUserInfo(char* username);
    int main(int argc, char **argv){
    	if(argc != 2) {
        	printf("Usage: ./a.out username\n");
        	return -1;
        }
        char *username = getUsername();
        printUserInfo(username);
    }

    char* getUsername(){
    	char *username = NULL;
    	int size = 0;
    	getline(&username, &size, stdin);
    	return username;
    }

    void printUserInfo(char* username){
    	char cmd[1024] = "cat /etc/passwd | grep ";
    	strcat(cmd, username);
    	system(cmd);
    }