import os

# Constants for flags
O_RDWR = os.O_RDWR | os.O_CREAT

# Open the file with read/write permissions, create if it doesn't exist
file_descriptor = os.open('config.txt', O_RDWR)

try:
    # Write string to the file
    os.write(file_descriptor, b'important_config')
finally:
    # Close the file descriptor
    os.close(file_descriptor)