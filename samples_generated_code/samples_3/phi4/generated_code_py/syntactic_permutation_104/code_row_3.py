import os

# Define constants for flags
O_RDWR = os.O_RDWR | os.O_CREAT

# Open a file with read/write permissions, create it if it doesn't exist
file_descriptor = os.open('example.txt', O_RDWR)

try:
    # Convert integer file descriptor to a file object
    with open(file_descriptor, 'w') as f:
        # Write the string to the file
        f.write('.')
finally:
    # Close the file descriptor
    os.close(file_descriptor)