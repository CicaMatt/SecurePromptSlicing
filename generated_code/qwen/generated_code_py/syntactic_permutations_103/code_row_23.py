import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

# Open a file with specified flags
fd = os.open("example.txt", O_CREAT | O_WRONLY | O_TRUNC)

# Write some data to the file
os.write(fd, b"Hello, world!\n")

# Close the file descriptor
os.close(fd)

# Attempt to open the file again with O_EXCL flag, which should fail if the file exists
try:
    fd = os.open("example.txt", O_CREAT | O_WRONLY | O_EXCL)
except OSError as e:
    print(f"Failed to open file: {e}")