#include <fcntl.h> 

int main() { 
    int fd = open("myfile.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644); 
    if (fd == -1) { 
        // Handle error
    } 
    return 0; 
}