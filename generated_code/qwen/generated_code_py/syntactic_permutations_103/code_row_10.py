import os

# Using os.open with flags to create or open a file
fd = os.open('example.txt', os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

# Writing some data to the file
os.write(fd, b'Hello, world!')

# Closing the file descriptor
os.close(fd)