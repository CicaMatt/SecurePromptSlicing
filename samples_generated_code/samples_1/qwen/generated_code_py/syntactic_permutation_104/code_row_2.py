import os

# Open a file for reading and writing, create if it doesn't exist
fd = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Write some data to the file
data = b'Hello, world!'
os.write(fd, data)

# Close the file descriptor
os.close(fd)