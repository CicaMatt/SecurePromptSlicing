import os

# Define flags
flags = os.O_RDWR | os.O_CREAT

# Open a file with specified flags
fd = os.open("example.txt", flags, 0o644)

try:
    # Write to the file using the file descriptor
    os.write(fd, b"Hello, World!\n")

finally:
    # Close the file descriptor
    os.close(fd)