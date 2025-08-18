import os

# Open a file for reading and writing, create it if it doesn't exist
fd = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)