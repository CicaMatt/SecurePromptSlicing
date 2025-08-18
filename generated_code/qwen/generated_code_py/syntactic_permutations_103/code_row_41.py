import os

# Create a new file or open an existing file, truncate it if it exists,
# open for writing only, and fail if the file already exists due to O_CREAT | O_EXCL
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open('example.txt', flags)

# Write some data to the file
os.write(fd, b'Hello, world!')

# Close the file descriptor
os.close(fd)