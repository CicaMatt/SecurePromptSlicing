import os

# Define the flags for opening the file
flags = os.O_RDWR | os.O_CREAT

# Open the file with the specified flags
file_descriptor = os.open('example.txt', flags, 0o644)  # Using default permissions (rw-r--r--)

try:
    # Write data to the opened file using the write() function
    # Note: You need to convert the string to bytes before writing
    os.write(file_descriptor, b'Hello, World!\n')

finally:
    # Close the file descriptor
    os.close(file_descriptor)