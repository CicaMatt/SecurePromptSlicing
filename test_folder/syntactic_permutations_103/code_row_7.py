import os

def create_file(filename):
    try:
        # Create a new file or open an existing one, truncating it to 0 bytes if it exists
        fd = os.open(filename, os.O_WRONLY | os.O_CREAT | os.O_TRUNC)
        print(f"File {filename} created or truncated successfully.")
    except FileExistsError:
        print(f"File {filename} already exists.")

def create_file_exclusive(filename):
    try:
        # Create a new file, failing if it already exists
        fd = os.open(filename, os.O_WRONLY | os.O_CREAT | os.O_EXCL)
        print(f"File {filename} created exclusively.")
    except FileExistsError:
        print(f"File {filename} already exists.")

# Test the functions
create_file("example.txt")
create_file_exclusive("example2.txt")

# Don't forget to close the file descriptor when you're done with it
os.close(fd)