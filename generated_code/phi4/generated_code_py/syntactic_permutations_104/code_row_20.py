import os

# Open or create the file with read/write permissions
file_descriptor = os.open('config.txt', os.O_RDWR | os.O_CREAT)

try:
    # Write to the file using the write() function
    os.write(file_descriptor, b'important_config')
finally:
    # Ensure that the file is closed properly
    os.close(file_descriptor)