import os

def create_or_open_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
        print(f"File {filename} created or truncated successfully")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")

def create_file_exclusive(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        print(f"File {filename} created exclusively")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")

# Example usage
filename1 = "example.txt"
fd1 = create_or_open_file(filename1)

filename2 = "exclusive_example.txt"
fd2 = create_file_exclusive(filename2)