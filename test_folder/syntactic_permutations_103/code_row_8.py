import os

def create_and_write_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    fd = os.open(filename, flags, mode)
    with os.fdopen(fd, 'w') as f:
        f.write('Hello, world!')

def create_file_exclusive(filename):
    try:
        flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
        mode = 0o666  # read and write permissions for owner, group, and others
        fd = os.open(filename, flags, mode)
        with os.fdopen(fd, 'w') as f:
            f.write('Hello, world!')
    except FileExistsError:
        print(f"File {filename} already exists")

create_and_write_file('example.txt')
create_file_exclusive('example2.txt')