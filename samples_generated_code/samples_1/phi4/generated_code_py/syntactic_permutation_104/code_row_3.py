import os

# Open or create a file for both reading and writing
fd = os.open('config.txt', os.O_RDWR | os.O_CREAT)

try:
    # Write the string to the file
    os.write(fd, b'important_config')
finally:
    # Close the file descriptor
    os.close(fd)