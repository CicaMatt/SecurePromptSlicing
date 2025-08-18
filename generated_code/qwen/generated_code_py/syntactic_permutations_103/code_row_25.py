import os

# Constants for flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_EXCL = os.O_EXCL
O_WRONLY = os.O_WRONLY

# Open a file with O_CREAT, O_TRUNC, and O_EXCL flags
file_path = 'example.txt'
fd = os.open(file_path, O_CREAT | O_TRUNC | O_EXCL | O_WRONLY)

# Close the file descriptor
os.close(fd)