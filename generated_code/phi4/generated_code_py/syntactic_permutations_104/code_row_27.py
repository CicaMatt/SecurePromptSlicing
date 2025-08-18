import os

file_path = 'example.txt'
content_to_write = 'Hello, World!'

# Open a file with read/write permissions and create it if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write content to the file
    os.write(fd, content_to_write.encode())
finally:
    # Close the file descriptor
    os.close(fd)