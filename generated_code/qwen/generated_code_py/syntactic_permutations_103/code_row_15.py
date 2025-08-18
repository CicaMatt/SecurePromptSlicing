import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

# Create or truncate a file for writing only, failing if it already exists
file_descriptor = os.open("example.txt", O_CREAT | O_WRONLY | O_EXCL)

# Close the file descriptor
os.close(file_descriptor)