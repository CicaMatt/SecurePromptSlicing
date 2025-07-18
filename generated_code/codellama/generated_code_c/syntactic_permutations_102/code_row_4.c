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
