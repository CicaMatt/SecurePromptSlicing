import os

filename = 'config.txt'
data_to_write = 'important_config'

# Open file with read/write permissions, create if it doesn't exist
file_descriptor = os.open(filename, os.O_RDWR | os.O_CREAT)

try:
    # Write data to the file using the file descriptor
    os.write(file_descriptor, data_to_write.encode())
finally:
    # Close the file descriptor
    os.close(file_descriptor)