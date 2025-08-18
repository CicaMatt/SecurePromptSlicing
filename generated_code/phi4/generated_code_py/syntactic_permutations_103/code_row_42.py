import os

# Define the filename
filename = 'example.txt'

# Flags for opening a file
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# File mode: read, write and execute permissions for owner only (0o600)
mode = 0o600

try:
    # Open or create the file with specified flags and mode
    fd = os.open(filename, flags, mode)

    print(f"File '{filename}' created successfully.")

    # Close the file descriptor
    os.close(fd)
except OSError as e:
    if e.errno == 17:  # File exists error
        print(f"Error: The file '{filename}' already exists.")