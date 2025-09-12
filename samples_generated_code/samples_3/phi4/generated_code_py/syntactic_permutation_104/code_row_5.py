import os

# Define the filename and content to write
filename = "important_config.txt"
content = "important_config"

# Open the file with read/write permissions, create if it doesn't exist
fd = os.open(filename, os.O_RDWR | os.O_CREAT)

try:
    # Seek to the start of the file before writing
    os.lseek(fd, 0, os.SEEK_SET)
    
    # Write content to the file
    os.write(fd, content.encode())
finally:
    # Close the file descriptor
    os.close(fd)