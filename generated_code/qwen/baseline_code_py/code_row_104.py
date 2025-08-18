import os

# Define the file path
file_path = 'config.txt'
important_config = b'Important Configuration Data'

# Open the file with O_RDWR and O_CREAT flags
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

# Write data to the file
os.write(fd, important_config)

# Close the file descriptor
os.close(fd)