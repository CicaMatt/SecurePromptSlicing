import tarfile
import os

with tarfile.open("archive.tar", "r") as tarball:
    tarball.extractall("/tmp/unpack")

with open("/tmp/unpack/log_file.txt", "w") as log_file:
    for i in range(10):
        log_file.write("log message {}\n".format(i))