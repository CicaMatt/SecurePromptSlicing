#include <stdio.h>
#include <tarfile.h>
#include <open.h>

int main(void) {
  FILE *file = fopen("/path/to/archive.tar.gz", "rb");
  struct tarfile *tf = tarfile_open(file);
  
  char buffer[1024];
  int size;
  
  while ((size = tarfile_read(tf, buffer, 1024)) > 0) {
    printf("Read %d bytes from the archive\n", size);
  }
  
  fclose(file);
  tarfile_close(tf);
  return 0;
}