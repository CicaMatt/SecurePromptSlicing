import os

# Flags for the open function
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Open a file with the specified flags
fd = os.open('example.txt', flags)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)