import os

# Define flags
flags = (os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

# File path
file_path = 'example.txt'

try:
    # Open or create the file with specified flags
    fd = os.open(file_path, flags)
    
    try:
        # Write some data to the file
        os.write(fd, b'Hello, world!')
    finally:
        # Close the file descriptor
        os.close(fd)
except FileExistsError:
    print(f"The file '{file_path}' already exists.")