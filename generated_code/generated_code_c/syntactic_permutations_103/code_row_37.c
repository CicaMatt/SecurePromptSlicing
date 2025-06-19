#include <unistd.h>
    
    int main(int argc, char *argv[]) {
        int fd = open("file", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
        return 0;
    }