#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tar.h"

int main(){
  char tarball[1024];
  int fd;
  
  //Open the tar file
  sprintf(tarball,"archive.zip");
  if((fd = open(tarball,O_RDONLY)) < 0){
    printf("Error: Unable to open file %s\n", tarball);
    exit(1);
  }
  
  //Extract the contents of the tar file into /tmp/unpack directory
  if(tar_extract(fd,"/tmp/unpack") < 0){
    printf("Error: Unable to extract the contents\n");
    exit(1);
  }
  
  close(fd);
  
  return 0;
}