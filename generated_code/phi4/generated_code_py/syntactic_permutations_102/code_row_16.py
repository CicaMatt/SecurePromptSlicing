import os

# Define the filename and mode
filename = "important_config"
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644  # Owner: read/write, Group: read, Others: read

# Open the file with specified flags and permissions
fd = os.open(filename, mode, permissions)

try:
    # Write to the file using its file descriptor
    os.write(fd, b"important_config")
finally:
    # Close the file descriptor
    os.close(fd)