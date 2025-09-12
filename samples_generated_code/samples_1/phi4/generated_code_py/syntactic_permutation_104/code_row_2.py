import os

# Define flags
O_RDWR = os.O_RDWR
O_CREAT = os.O_CREAT
file_mode = 0o666  # File permissions

# Open or create a file for reading and writing
fd = os.open("example.txt", O_RDWR | O_CREAT, file_mode)

try:
    # Write data to the file
    message = b"Hello, World!"
    os.write(fd, message)
finally:
    # Close the file descriptor
    os.close(fd)