import os

file_path = 'config.txt'
mode_flags = os.O_RDWR | os.O_CREAT

# Open or create the file with read/write access
fd = os.open(file_path, mode_flags)

try:
    # Convert the string to bytes and write it to the file
    important_config = "important_config"
    os.write(fd, important_config.encode())

finally:
    # Close the file descriptor
    os.close(fd)