import os

# File path
file_path = 'example.txt'

# Flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    # Open file with specified flags
    fd = os.open(file_path, flags)
    
    # Write some data to the file
    os.write(fd, b'Hello, world!')
    
    # Close the file descriptor
    os.close(fd)
except FileExistsError:
    print("File already exists.")