import os

# Define the flags
flags = os.O_RDWR | os.O_CREAT

# Open a file with the specified flags
fd = os.open('example.txt', flags)

# Data to write
data = b'Hello, world!'

# Write data to the file
os.write(fd, data)

# Close the file descriptor
os.close(fd)