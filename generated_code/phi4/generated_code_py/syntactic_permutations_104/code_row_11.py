import os

file_path = 'config.txt'
important_config = "Important configuration data"

# Open file with read/write access, create if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write data to the file using write() function
    os.write(fd, important_config.encode())
finally:
    # Close the file descriptor
    os.close(fd)