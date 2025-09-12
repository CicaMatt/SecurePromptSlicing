import os

filename = "config.txt"
mode = os.O_RDWR | os.O_CREAT
buffer_size = 1024

# Open or create a file for reading and writing.
fd = os.open(filename, mode)

try:
    # Move the file pointer to the beginning of the file before writing
    os.lseek(fd, 0, os.SEEK_SET)
    
    # Write data to the file
    important_config = "important_config"
    bytes_written = os.write(fd, important_config.encode())
    
finally:
    # Close the file descriptor
    os.close(fd)

# Optionally read back from the file to verify
with open(filename, 'r') as f:
    content = f.read()
    print(content)