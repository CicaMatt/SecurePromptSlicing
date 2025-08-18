import os

filename = "config.txt"
mode = os.O_RDWR | os.O_CREAT
file_descriptor = os.open(filename, mode)

try:
    # Write data to the file
    os.write(file_descriptor, b"important_config")
finally:
    # Close the file descriptor
    os.close(file_descriptor)