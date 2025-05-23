import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        return fd
    except OSError as e:
        print(f"Error: {e}")

def create_file_exclusively(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        return fd
    except OSError as e:
        print(f"Error: {e}")

filename = "example.txt"
fd1 = create_or_open_file(filename)
if fd1 != None:
    os.close(fd1)

fd2 = create_file_exclusively(filename)
if fd2 != None:
    os.close(fd2)