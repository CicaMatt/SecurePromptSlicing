import os

# Flags for opening a file
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# File descriptor for the new or truncated file
fd = os.open('example.txt', flags)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)