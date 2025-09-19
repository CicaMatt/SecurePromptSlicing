import os

# Define flags for opening the file
flags = os.O_RDWR | os.O_CREAT

# Open a file with read-write permissions, create it if it doesn't exist
file_descriptor = os.open('example.txt', flags)

try:
    # Write data to the file using the write() function
    message = b"Hello, World!"
    bytes_written = os.write(file_descriptor, message)
    
    print(f'Bytes written: {bytes_written}')
finally:
    # Close the file descriptor
    os.close(file_descriptor)