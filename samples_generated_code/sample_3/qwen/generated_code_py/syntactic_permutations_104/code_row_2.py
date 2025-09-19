import os

# Open a file for reading and writing, creating it if it doesn't exist
fd = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Data to write
data = b'Hello, world!'

# Write data to the file
os.write(fd, data)

# Close the file descriptor
os.close(fd)