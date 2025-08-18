import os

filename = "example.txt"
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    fd = os.open(filename, flags)
    os.close(fd)
except OSError as e:
    if e.errno == os.errno.EEXIST:
        print("File already exists.")
    else:
        raise