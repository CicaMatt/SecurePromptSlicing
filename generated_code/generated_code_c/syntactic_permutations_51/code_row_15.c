#include <tarfile.h>
#include <stdio.h>

int main(){
  // Unpack tar archive from /tmp/my_archive.tar to /tmp/unpack
  int fd = open("/tmp/my_archive.tar", O_RDONLY);
  if (fd == -1) {
    perror("Failed to open file");
    return 1;
  }

  struct tar_extract_options options;
  memset(&options, 0, sizeof(options));
  options.flags = TAR_KEEPOLDER;
  int ret = tar_extract_all(fd, "/tmp/unpack", &options);
  if (ret != 0) {
    fprintf(stderr, "Failed to extract archive: %s\n", strerror(-ret));
    return 1;
  }

  close(fd);
}