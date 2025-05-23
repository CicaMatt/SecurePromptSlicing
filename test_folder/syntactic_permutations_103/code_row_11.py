import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    fd = os.open(filename, flags)
    try:
        with os.fdopen(fd, 'w') as f:
            f.write("Hello World!")
    finally:
        os.close(fd)

def exclusive_create_file(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        try:
            with os.fdopen(fd, 'w') as f:
                f.write("Hello World!")
        finally:
            os.close(fd)
    except FileExistsError:
        print(f"File {filename} already exists")

create_or_open_file('test.txt')
exclusive_create_file('test2.txt')