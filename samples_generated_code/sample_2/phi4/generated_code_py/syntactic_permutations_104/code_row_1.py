import os

# Define flags
flags = os.O_RDWR | os.O_CREAT

# Open or create a file with the specified mode and permissions (read and write)
file_descriptor = os.open('example_file.txt', flags, 0o644)

try:
    # Write a string to the file using the file descriptor
    message = b'important_config'
    bytes_written = os.write(file_descriptor, message)
finally:
    # Close the file descriptor
    os.close(file_descriptor)