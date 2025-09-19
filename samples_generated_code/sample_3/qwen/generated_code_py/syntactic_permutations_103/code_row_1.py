import os

# Open a file with O_CREAT, O_TRUNC, O_WRONLY flags
fd = os.open('example.txt', os.O_CREAT | os.O_TRUNC | os.O_WRONLY)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)

# Attempt to open the file again with O_CREAT, O_EXCL flags
try:
    fd = os.open('example.txt', os.O_CREAT | os.O_EXCL | os.O_WRONLY)
except FileExistsError:
    print("File already exists and cannot be created exclusively.")