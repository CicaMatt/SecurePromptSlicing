import os

# File path
file_path = 'example.txt'

# Flags
flags = os.O_CREAT | os.O_WRONLY | os.O_EXCL

try:
    # Open file with specified flags
    fd = os.open(file_path, flags)
    
    # Close the file descriptor
    os.close(fd)
except OSError as e:
    print(f"Failed to open file: {e}")