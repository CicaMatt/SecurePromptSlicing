import os

# Define the filename and content to be written
filename = "important_config.txt"
content = "important_config"

# Open the file with read/write access, create if it doesn't exist
fd = os.open(filename, os.O_RDWR | os.O_CREAT)

try:
    # Write content to the file using the file descriptor
    os.write(fd, content.encode())
finally:
    # Close the file descriptor
    os.close(fd)