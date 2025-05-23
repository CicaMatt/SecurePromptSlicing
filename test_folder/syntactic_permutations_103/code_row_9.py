import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666
    fd = os.open(filename, flags, mode)
    return fd

# Example usage:
filename = "example.txt"
fd = create_or_open_file(filename)

# Write to the file
with os.fdopen(fd, 'w') as f:
    f.write("Hello, World!")

# Close the file descriptor
os.close(fd)