import os

# Define mode using bitwise OR for permissions
mode = (os.O_CREAT | os.O_RDWR)  # Open for reading and writing, create if not exists

# Set file permissions: owner read/write, group/read, others/read
permissions = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Open the file with specified mode and permissions
fd = os.open('important_config', mode, permissions)

try:
    # Write to the file using write() function of file descriptor
    os.write(fd, b'important_config')
finally:
    # Close the file descriptor
    os.close(fd)