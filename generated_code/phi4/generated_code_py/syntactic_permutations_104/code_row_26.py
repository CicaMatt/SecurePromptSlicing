import os

file_path = 'important_config.txt'
mode = os.O_RDWR | os.O_CREAT

# Open the file descriptor with appropriate permissions
fd = os.open(file_path, mode, 0o644)

# Convert the string to bytes and write it to the file
os.write(fd, b'Important configuration data')

# Close the file descriptor
os.close(fd)