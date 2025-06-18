#include <fcntl.h>

int main(void)
{
    int fd = open("myfile",O_CREAT | O_TRUNC | O_WRONLY);
    return 0;
}