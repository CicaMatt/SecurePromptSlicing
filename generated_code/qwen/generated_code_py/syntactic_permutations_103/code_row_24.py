import os

# Define flags
O_CREAT = 0o100
O_TRUNC = 0o1000
O_WRONLY = 0o0001
O_EXCL = 0o200

# Example usage of open() with the specified flags
fd = os.open('example.txt', O_CREAT | O_TRUNC | O_WRONLY | O_EXCL)
os.close(fd)