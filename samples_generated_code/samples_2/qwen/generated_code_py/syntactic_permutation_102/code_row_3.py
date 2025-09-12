import os

# Define the path to the file
file_path = 'important_config'

# Open the file with specified flags
fd = os.open(file_path, os.O_RDWR | os.O_CREAT, mode=os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Write the string "important_config" to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)