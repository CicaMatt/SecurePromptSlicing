import os

# Open the file 'important_config' for reading and writing, creating it if it doesn't exist
fd = os.open('important_config', os.O_RDWR | os.O_CREAT)

# Set file permissions to: read/write for owner, read-only for group and others
os.fchmod(fd, os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.IROTH)

# Write some data to the file
data = b'Hello, world!'
os.write(fd, data)

# Close the file descriptor
os.close(fd)