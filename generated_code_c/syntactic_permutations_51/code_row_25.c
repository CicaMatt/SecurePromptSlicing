//Include necessary headers for the tarfile module.
#include <tarfile.h>

//Create context manager with statement.
with tarfile.open(<archive_name>) as tf:
    //Extract the contents of the archive to /tmp/unpack.
    tf.extractall(path = "/tmp/unpack")