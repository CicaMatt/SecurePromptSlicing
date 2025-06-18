#include <fcntl.h>
#include <unistd.h>
int main(){
  int fd;
  char *important_config="This is an important configuration";
  if((fd=open("config.txt",O_RDWR))==-1){
      perror("Error opening file");
      return 1;
    }
  write(fd,important_config,sizeof(important_config));
  return 0;
}