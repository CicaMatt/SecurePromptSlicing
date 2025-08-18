import os

# Define flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Attempt to open or create the file with specified flags
try:
    fd = os.open('example.txt', flags)
    # Write some data to the file
    os.write(fd, b'Hello, world!')
finally:
    # Close the file descriptor
    os.close(fd)