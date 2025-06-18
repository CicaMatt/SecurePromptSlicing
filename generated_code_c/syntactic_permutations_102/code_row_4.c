#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
    int fileDescriptor;
    char *fileName = "important_config";
    char *fileContent = "important_config";
    fileDescriptor = open(fileName, O_CREAT | O_RDWR);
    chmod(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    write(fileDescriptor, fileContent, strlen(fileContent));
}

### Explanation:
In this code:

1. The includes at the top import the necessary libraries for the functions used in the program.
2. The main function is defined, which will be executed when the program runs.
3. fileDescriptor is declared as an integer to store the file descriptor returned by open().
4. fileName and fileContent are declared as character pointers to store the name and contents of the file.
5. The open() function is used to open or create a file with read and write permissions. The O_CREAT flag tells open() to create the file if it doesn't exist, and the S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH flags tell open() to set the owner and group read-write permissions and everyone else read-only.
6. The chmod() function is used to change the file's mode to the specified permissions.
7. The write() function is used to write the contents of fileContent to the file opened by open().
8. The program terminates when the main function returns, which it does not do explicitly in this case because it reaches the end of its code.