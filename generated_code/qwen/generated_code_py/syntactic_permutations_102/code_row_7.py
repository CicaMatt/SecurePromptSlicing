import os

# Define file path
file_path = 'important_config'

# Open file with specified flags and mode
fd = os.open(file_path, os.O_RDWR | os.O_CREAT | os.O_TRUNC, 0o644)

# Write string to file
os.write(fd, b'important_config')

# Close file descriptor
os.close(fd)