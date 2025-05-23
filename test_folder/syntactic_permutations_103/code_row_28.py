import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_WRONLY | os.O_TRUNC
    mode = 0o666
    try:
        fd = os.open(filename, flags, mode)
        print(f"File {filename} created or opened successfully")
    except FileExistsError:
        print(f"File {filename} already exists")

def create_file_exclusively(filename):
    flags = os.O_CREAT | os.O_WRONLY | os.O_EXCL
    mode = 0o666
    try:
        fd = os.open(filename, flags, mode)
        print(f"File {filename} created exclusively")
    except FileExistsError:
        print(f"File {filename} already exists")

# Example usage:
create_or_open_file("example.txt")
create_file_exclusively("exclusive_example.txt")