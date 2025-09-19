import os

# Define the flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Open the file with the specified flags
fd = os.open('example.txt', flags)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)