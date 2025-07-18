#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tarfile.h>
#include <fcntl.h>

int main()
{
    //Create a new file in the /tmp/unpack directory with write permission using O_CREAT and O_TRUNC flags.
    int fd = open("/tmp/unpack", O_WRONLY | O_CREAT, 0777);

    if (fd < 0)
    {
        printf("Error opening file\n");
        return 1;
    }

    //Create a new tarfile object and open the archive.
    struct tarfile *tar = tarfile_open("/path/to/archive.tar.gz", "r:gz");

    if (tar == NULL)
    {
        printf("Error opening tarfile\n");
        return 1;
    }

    //Extract the contents of the archive to the file descriptor.
    int status = tarfile_extractall(tar, fd);

    if (status != 0)
    {
        printf("Error extracting archive\n");
        return 1;
    }

    //Close the tarfile object.
    tarfile_close(tar);

    //Close the file descriptor.
    close(fd);

    return 0;
}