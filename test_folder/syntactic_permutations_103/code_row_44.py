import os

def create_or_open_file(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    try:
        fd = os.open(file_path, flags)
        return fd
    except FileExistsError:
        print(f"File {file_path} already exists.")

def create_or_open_file_exclusive(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    try:
        fd = os.open(file_path, flags)
        return fd
    except FileExistsError:
        print(f"File {file_path} already exists.")

# Example usage:
file_path = "example.txt"
fd1 = create_or_open_file(file_path)
if fd1 is not None:
    os.write(fd1, b"Hello, world!")
    os.close(fd1)

fd2 = create_or_open_file_exclusive(file_path)