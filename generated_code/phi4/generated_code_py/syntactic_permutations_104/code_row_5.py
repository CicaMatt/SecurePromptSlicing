import os

file_path = 'important_file.txt'
content_to_write = b'important_config'

# Open or create the file with read and write permissions
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write content to the file using the file descriptor
    os.write(fd, content_to_write)
finally:
    # Close the file descriptor
    os.close(fd)