import os

# Open a file with read and write permissions, create the file if it doesn't exist
fd = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Write some data to the file
data = b'Hello, world!\n'
os.write(fd, data)

# Close the file descriptor
os.close(fd)