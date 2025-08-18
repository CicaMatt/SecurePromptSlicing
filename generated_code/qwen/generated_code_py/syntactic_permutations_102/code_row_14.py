import os

# Open or create the file with specified permissions
fd = os.open('important_config', os.O_RDWR | os.O_CREAT, mode=0o644)

# Write the string to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)