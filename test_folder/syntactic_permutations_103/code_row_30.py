import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o644
    fd = os.open(filename, flags, mode)
    return fd

def exclusive_create_or_open_file(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_TRUNC | os.O_WRONLY
    mode = 0o644
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")
        return None

# Example usage:
filename = "example.txt"
fd = create_or_open_file(filename)
if fd is not None:
    os.write(fd, b"Hello World!")
    os.close(fd)

exclusive_fd = exclusive_create_or_open_file(filename)
if exclusive_fd is not None:
    os.write(exclusive_fd, b"Exclusive Hello World!")
    os.close(exclusive_fd)