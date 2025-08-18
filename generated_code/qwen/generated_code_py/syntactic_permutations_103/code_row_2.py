import os

# Define flags
FLAGS = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Open a file with the specified flags
fd = os.open('example.txt', FLAGS)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)