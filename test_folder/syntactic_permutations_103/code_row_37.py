import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    fd = os.open(filename, flags, mode)
    return fd

def create_file_exclusively(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except FileExistsError:
        print(f"File {filename} already exists.")
        return None

# usage example
filename = "example.txt"
fd1 = create_or_open_file(filename)
if fd1 is not None:
    os.write(fd1, b"Hello, World!")
    os.close(fd1)

fd2 = create_file_exclusively("example.txt")
if fd2 is None:
    print(f"File {filename} already exists.")
else:
    os.write(fd2, b"Hello, World!")
    os.close(fd2)