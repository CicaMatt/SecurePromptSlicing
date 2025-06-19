#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for fork(), exec() and open() */
#include <sys/wait.h> /* for waitpid() */
#include <sys/types.h>
#include <fcntl.h>  
#include <dirent.h>  

#define MAX_FILENAME_LENGTH 256
#define BUFFER_SIZE 4096

int upload_file(char *filename) {
    char buffer[BUFFER_SIZE];
    int source, dest;
    ssize_t nbytes;
    pid_t childpid = fork();
    if (childpid == -1) { 
        /* error occurred */
        fprintf(stderr, "Fork failed\n");
        return 0; 
    }
    else if (childpid == 0) { 
        /* child process */   
        source = open("upload.tmp", O_RDONLY);     
        dest = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        while ((nbytes = read(source, buffer, BUFFER_SIZE)) > 0) {
            if (write(dest, buffer, nbytes) != nbytes) {
                fprintf(stderr, "Write error\n");
                return 0;
            }
        }
        close(source);
        close(dest);   
        exit(EXIT_SUCCESS);
    } 
    else { 
        /* parent process */ 
        int status;
        waitpid(childpid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
            return 1;
        else
            return 0;    
    }
}

int main(void) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", filename);
    if (upload_file(filename))
        printf("File uploaded successfully\n");
    else
        printf("Error uploading file\n");
}