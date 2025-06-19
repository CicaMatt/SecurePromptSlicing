#include <unistd.h>

int main(){
  int fd = open("configuration.txt", O_RDWR|O_CREAT);
  if (fd == -1){
    printf("Error opening file\n");
  } else{
    write(fd, "important_config", strlen("important_config"));
  }
  return 0;
}