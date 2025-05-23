import os

def create_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY | os.O_EXCL)
        print(f"File {filename} created successfully")
        os.close(fd)
    except FileExistsError:
        print(f"File {filename} already exists")

def truncate_file(filename):
    try:
        fd = os.open(filename, os.O_WRONLY | os.O_TRUNC)
        print(f"File {filename} truncated successfully")
        os.close(fd)
    except FileNotFoundError:
        print(f"File {filename} does not exist")

# Example usage
create_file("example.txt")
truncate_file("example.txt")