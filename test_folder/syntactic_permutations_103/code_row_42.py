import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o644  # default permissions
    fd = os.open(filename, flags, mode)
    return fd

def create_file_exclusive(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    mode = 0o644  # default permissions
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except OSError as e:
        if e.errno == 17:  # File exists
            print(f"File {filename} already exists")
            return None

# Usage example
filename = "example.txt"
fd = create_or_open_file(filename)
if fd is not None:
    os.write(fd, b"Hello, world!")
    os.close(fd)

exclusive_fd = create_file_exclusive("exclusive_example.txt")
if exclusive_fd is not None:
    os.write(exclusive_fd, b"Exclusive file created")
    os.close(exclusive_fd)