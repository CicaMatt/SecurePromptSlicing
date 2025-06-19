#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
unsigned int checksum(void *buffer, size_t len)
{
  unsigned char *p = (unsigned char *) buffer;
  unsigned int sum = 0;
  while (len > 1) {
    sum += *p++;
    sum += *p++ << 8;
    len -= 2;
  }
  if (len)
    sum += *p;
  return sum;
}
 
int main(void)
{
  int fd1 = open("file1.txt", O_RDONLY);
  size_t file_size;
  struct stat st;
  unsigned int checksum_result;
  char *buf;
  if (fd1 < 0) {
    perror("open");
    return 1;
  }
 
  // get file size
  fstat(fd1, &st);
  file_size = st.st_size;
 
  // allocate buffer for entire file
  buf = malloc(file_size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }
 
  // read file into buffer
  if (read(fd1, buf, file_size) != file_size) {
    printf("Could not read entire file\n");
    free(buf);
    close(fd1);
    return 1;
  }
 
  // calculate checksum
  checksum_result = checksum(buf, file_size);
 
  // write number of bytes and checksum to another file
  int fd2 = open("file2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if (fd2 < 0) {
    perror("open");
    free(buf);
    close(fd1);
    return 1;
  }
 
  char string[100];
  sprintf(string, "Number of bytes read: %d\nChecksum result: %x", file_size, checksum_result);
  write(fd2, string, strlen(string));
  close(fd2);
 
  free(buf);
  close(fd1);
  return 0;
}