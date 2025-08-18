import os

file_path = 'important_file.txt'
file_content = b'important_config'

# Open the file with read/write access, create if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write content to the file
    os.write(fd, file_content)
finally:
    # Close the file descriptor
    os.close(fd)