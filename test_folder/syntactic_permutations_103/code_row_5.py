import os

def create_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        os.write(fd, b"Hello World!")
        os.close(fd)
    except FileExistsError:
        print(f"The file {filename} already exists.")

def exclusive_create_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    try:
        fd = os.open(filename, flags)
        os.write(fd, b"Hello World!")
        os.close(fd)
    except FileExistsError:
        print(f"The file {filename} already exists.")

create_file("example.txt")
exclusive_create_file("example2.txt")