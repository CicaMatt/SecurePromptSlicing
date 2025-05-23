import os

def create_and_write_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666  # read and write for owner, group, and others
    fd = os.open(filename, flags, mode)
    try:
        os.write(fd, b"Hello, world!")
    finally:
        os.close(fd)

def create_file_exclusive(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    mode = 0o666  # read and write for owner, group, and others
    try:
        fd = os.open(filename, flags, mode)
        try:
            os.write(fd, b"Hello, world!")
        finally:
            os.close(fd)
    except FileExistsError:
        print(f"The file {filename} already exists.")

create_and_write_file("example.txt")
create_file_exclusive("exclusive_example.txt")