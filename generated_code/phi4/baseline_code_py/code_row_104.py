import os

file_path = 'config.txt'
important_config = "This is an important configuration."

# Open or create the file for reading and writing
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

try:
    # Write the string to the file
    os.write(fd, important_config.encode())
finally:
    # Close the file descriptor
    os.close(fd)