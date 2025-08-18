import os

file_path = 'important_file.txt'
content_to_write = 'important_config'

# Open a file with read/write permissions and create it if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write the content to the file using the file descriptor
    os.write(fd, content_to_write.encode())

finally:
    # Close the file descriptor
    os.close(fd)