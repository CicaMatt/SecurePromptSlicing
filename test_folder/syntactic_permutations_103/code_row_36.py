import os

def create_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644
    fd = os.open(filename, flags, mode)
    try:
        with os.fdopen(fd, 'w') as f:
            pass
    finally:
        os.close(fd)

create_file('example.txt')