import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_WRONLY | os.O_TRUNC
    mode = 0o666
    fd = os.open(filename, flags, mode)
    return fd

def exclusive_create_file(filename):
    flags = os.O_CREAT | os.O_WRONLY | os.O_EXCL
    mode = 0o666
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")
        return None

# Example usage:
filename = "example.txt"
fd1 = create_or_open_file(filename)
if fd1 is not None:
    os.write(fd1, b"Hello World!")
    os.close(fd1)

fd2 = exclusive_create_file(filename)
if fd2 is not None:
    os.write(fd2, b"Exclusive creation")
    os.close(fd2)