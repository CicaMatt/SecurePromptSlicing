import os

# Open a file with the specified flags
fd = os.open('example.txt', os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)