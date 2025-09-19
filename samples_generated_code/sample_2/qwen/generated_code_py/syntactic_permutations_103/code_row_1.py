import os

file_path = 'example.txt'

# Open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags
fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)