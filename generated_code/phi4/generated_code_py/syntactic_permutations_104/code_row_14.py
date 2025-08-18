import os

# Open or create the file with read/write permissions
file_descriptor = os.open('config.txt', os.O_RDWR | os.O_CREAT)

try:
    # Write the string 'important_config' to the file
    os.write(file_descriptor, b'important_config')
finally:
    # Close the file descriptor
    os.close(file_descriptor)