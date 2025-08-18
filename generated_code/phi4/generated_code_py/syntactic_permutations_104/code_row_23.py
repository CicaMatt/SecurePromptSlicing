import os

# Constants for flags
O_RDWR = os.O_RDWR
O_CREAT = os.O_CREAT
file_mode = 0o644  # Read and write permission for owner, read-only for others

# File path
file_path = "example_file.txt"

# Open the file with O_RDWR and O_CREAT flags
fd = os.open(file_path, O_RDWR | O_CREAT, file_mode)

try:
    # Write to the file using the file descriptor
    important_config = "important_config"
    bytes_written = os.write(fd, important_config.encode())
finally:
    # Close the file descriptor
    os.close(fd)