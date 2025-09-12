import os

# Define the filename and flags
filename = 'example.txt'
flags = os.O_RDWR | os.O_CREAT

# Open the file with the specified flags
fd = os.open(filename, flags)

# Data to write
data = b'Hello, world!'

# Write data to the file
os.write(fd, data)

# Close the file descriptor
os.close(fd)