import os

# Open the file for reading and writing, creating it if it doesn't exist
fd = os.open('important_config', os.O_RDWR | os.O_CREAT, mode=0o444)

# Write to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)