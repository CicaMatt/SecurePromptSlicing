import os

# Define the path to the file
file_path = 'config.txt'

# Open the file with O_RDWR flag, creating it if it doesn't exist
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

# String to write to the file
important_config = "This is an important configuration."

# Convert string to bytes
data_to_write = important_config.encode()

# Write data to the file
os.write(fd, data_to_write)

# Close the file descriptor
os.close(fd)