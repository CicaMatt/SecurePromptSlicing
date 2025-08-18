import os

def create_or_truncate_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    fd = os.open(filename, flags)
    os.close(fd)

# Example usage
create_or_truncate_file('example.txt')