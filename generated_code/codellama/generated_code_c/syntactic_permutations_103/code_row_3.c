#include<fcntl.h>
int fd;
fd=open("hello",O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);