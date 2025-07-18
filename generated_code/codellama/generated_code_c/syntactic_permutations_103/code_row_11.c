#include<fcntl.h>
int fd;
fd = open("myfile",O_WRONLY|O_CREAT|O_EXCL,0644);
if(fd==-1){
    //handle error
}