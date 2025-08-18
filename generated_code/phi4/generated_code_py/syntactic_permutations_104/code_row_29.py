import os

# Open (or create) the file in read/write mode
fd = os.open('important_config.txt', os.O_RDWR | os.O_CREAT)

try:
    # Convert the string to bytes and write it to the file descriptor
    os.write(fd, b'important_config')

finally:
    # Close the file descriptor
    os.close(fd)