import os

# Define the flags using os module constants
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    # Open a file with the specified flags
    fd = os.open('example.txt', flags)
    # Write some data to the file
    os.write(fd, b'Hello, world!')
finally:
    # Close the file descriptor
    os.close(fd)