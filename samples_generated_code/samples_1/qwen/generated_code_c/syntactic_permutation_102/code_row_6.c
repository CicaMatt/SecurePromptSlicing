#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    const char *data = "important_config";
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
    
    if (fd != -1) {
        write(fd, data, sizeof(data) - 1);
        close(fd);
    }
    
    return 0;
}