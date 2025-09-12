import os

# Define flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Open file with specified flags
fd = os.open('example.txt', flags)

# Close the file descriptor
os.close(fd)