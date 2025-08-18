import os

filename = 'config_file.txt'
content = b'important_config'

# Open file with read/write access, create if it doesn't exist.
fd = os.open(filename, os.O_RDWR | os.O_CREAT)

try:
    # Write content to the file using the file descriptor.
    os.write(fd, content)
finally:
    # Close the file descriptor.
    os.close(fd)