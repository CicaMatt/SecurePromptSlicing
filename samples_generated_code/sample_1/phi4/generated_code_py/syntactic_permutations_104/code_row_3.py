import os

filename = 'config.txt'
mode = os.O_RDWR | os.O_CREAT
buffer_size = 1024
important_config = "Important configuration data."

# Open or create the file with read and write permissions.
fd = os.open(filename, mode)

try:
    # Write the important_config string to the file.
    os.write(fd, important_config.encode())
finally:
    # Ensure the file is closed properly.
    os.close(fd)