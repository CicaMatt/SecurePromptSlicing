#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
int main(){
  int fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
}


### Explanation:

The include statements import the necessary functions and constants for working with files in C. The open() function creates a new file or opens an existing file.The O_CREAT flag () to create the file if it doesn't exist.The O_TRUNC flag () to truncate the file to 0 bytes if it already exists.The O_WRONLY flag () to open the file for writing only.The O_EXCL flag () to fail if the file already exists.