import os

# Open the file 'important_config' for reading and writing with specific permissions
fd = os.open('important_config', os.O_RDWR | os.O_CREAT, mode=0o644)

# Write the string 'important_config' to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)