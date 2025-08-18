import os

# Define the path to the file
file_path = 'important_file.txt'
# Define the content to write
content = b'important_config'

# Open the file with O_RDWR and O_CREAT flags
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)

# Write the content to the file
os.write(fd, content)

# Close the file descriptor
os.close(fd)