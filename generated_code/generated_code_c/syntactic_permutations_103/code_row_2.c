#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
  int fd;
  //create a new file or opens an existing file with the specified name and mode.
  if((fd = open("hello", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644)) == -1){
    perror("open");
    return 1;
  }
  //close file descriptor
  if((close(fd) == -1)){
    perror("close");
    return 1;
  }
  return 0;
}