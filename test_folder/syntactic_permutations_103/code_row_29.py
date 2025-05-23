import os

def create_and_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o644  # read and write permissions for owner, read permission for group and others
    fd = os.open(filename, flags, mode)
    return fd

def exclusive_create_and_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # read and write permissions for owner, read permission for group and others
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except OSError as e:
        if e.errno == 17:  # file already exists
            print(f"File {filename} already exists")
        else:
            raise

# example usage
filename = "example.txt"
fd1 = create_and_open_file(filename)
os.write(fd1, b"Hello, world!")
os.close(fd1)

try:
    fd2 = exclusive_create_and_open_file(filename)
    os.write(fd2, b"Hello again!")
    os.close(fd2)
except Exception as e:
    print(f"An error occurred: {e}")