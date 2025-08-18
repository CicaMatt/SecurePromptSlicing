import os

# Define the file path
file_path = 'important_config'

# Open the file with the specified flags and mode
fd = os.open(file_path, os.O_RDWR | os.O_CREAT, 0o644)

# Write the string to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)