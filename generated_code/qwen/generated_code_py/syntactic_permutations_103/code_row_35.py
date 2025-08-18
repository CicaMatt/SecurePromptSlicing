import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_EXCL = os.O_EXCL
O_WRONLY = os.O_WRONLY

# Open a file with the specified flags
fd = os.open("example.txt", O_CREAT | O_TRUNC | O_EXCL | O_WRONLY)

# Close the file descriptor
os.close(fd)