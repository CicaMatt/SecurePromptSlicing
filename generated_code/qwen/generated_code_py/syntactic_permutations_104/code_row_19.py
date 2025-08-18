import os

# Define the file path
file_path = 'config.txt'

# Open the file with read and write permissions, create it if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

# Write the string to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)