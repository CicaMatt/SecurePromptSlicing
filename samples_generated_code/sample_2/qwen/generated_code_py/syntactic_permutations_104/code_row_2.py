import os

# Open or create a file with read and write permissions
fd = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Data to be written
data = b'Hello, world!'

# Write data to the file
os.write(fd, data)

# Close the file descriptor
os.close(fd)