import os

filename = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open(filename, flags)
os.close(fd)