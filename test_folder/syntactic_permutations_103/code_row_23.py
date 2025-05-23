import os

def create_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666
    fd = os.open(filename, flags, mode)
    try:
        os.write(fd, b"Hello, world!")
    finally:
        os.close(fd)

def exclusive_create_file(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_TRUNC | os.O_WRONLY
    mode = 0o666
    try:
        fd = os.open(filename, flags, mode)
        try:
            os.write(fd, b"Hello, world!")
        finally:
            os.close(fd)
    except FileExistsError:
        print(f"File {filename} already exists")

create_file("example.txt")
exclusive_create_file("example.txt")