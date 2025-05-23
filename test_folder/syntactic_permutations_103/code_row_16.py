import os

def create_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY | os.O_EXCL)
        print(f"File {filename} created successfully")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")
        return None

def truncate_file(filename):
    try:
        fd = os.open(filename, os.O_WRONLY | os.O_TRUNC)
        print(f"File {filename} truncated successfully")
        return fd
    except FileNotFoundError:
        print(f"File {filename} does not exist")
        return None

# Create a new file or open an existing file for writing only
fd1 = create_file("example.txt")

# Truncate the file to 0 bytes if it already exists
fd2 = truncate_file("example.txt")

# Close the file descriptors
if fd1 is not None:
    os.close(fd1)
if fd2 is not None:
    os.close(fd2)