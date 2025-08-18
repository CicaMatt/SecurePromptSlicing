import os

# Define the filename
filename = 'example.txt'

# Use the flags as described: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Set permissions for the file, typically 0o644 (owner read/write, group and others read)
permissions = 0o644

try:
    # Open or create the file with specified flags and permissions
    fd = os.open(filename, flags, permissions)

    # Close the file descriptor
    os.close(fd)
    
except OSError as e:
    print(f"Error: {e.strerror}")