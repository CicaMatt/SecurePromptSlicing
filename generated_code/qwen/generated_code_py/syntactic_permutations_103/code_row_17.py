import os

# Define flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Open file with specified flags
fd = os.open('example.txt', flags)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)