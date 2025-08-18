import os

flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open('example.txt', flags)

# Writing some data to the file
os.write(fd, b'Hello, world!')

# Closing the file descriptor
os.close(fd)