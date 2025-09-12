import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.W_OK
O_EXCL = os.O_EXCL

# Open a file with specified flags
fd = os.open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL)

# Write to the file
os.write(fd, b"Hello, world!")

# Close the file descriptor
os.close(fd)