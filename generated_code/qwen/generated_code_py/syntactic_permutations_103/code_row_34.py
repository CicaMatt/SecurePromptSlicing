import os

# Define the flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY

# Open a file with the specified flags
fd = os.open('example.txt', flags)

# Close the file descriptor
os.close(fd)