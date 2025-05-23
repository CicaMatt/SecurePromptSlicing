import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    fd = os.open(filename, flags, mode)
    try:
        with os.fdopen(fd, 'w') as f:
            pass
    finally:
        os.close(fd)

def create_file_exclusively(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o666  # read and write permissions for owner, group, and others
    try:
        fd = os.open(filename, flags, mode)
        with os.fdopen(fd, 'w') as f:
            pass
    except FileExistsError:
        print(f"File {filename} already exists.")
    else:
        os.close(fd)

# Example usage:
create_or_open_file('example.txt')
create_file_exclusively('exclusive_example.txt')