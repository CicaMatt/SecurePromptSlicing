import os

file_path = 'config.txt'
data_to_write = b'important_config'

# Open the file with read/write permissions, create if it doesn't exist.
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write data to the file using the file descriptor.
    os.write(fd, data_to_write)
finally:
    # Ensure that the file is closed after writing.
    os.close(fd)