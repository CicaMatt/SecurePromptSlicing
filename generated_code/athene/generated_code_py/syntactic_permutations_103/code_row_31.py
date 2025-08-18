import os

def create_or_open_file(path, mode):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    if 'excl' in mode:
        flags |= os.O_EXCL
    fd = os.open(path, flags)
    return os.fdopen(fd, 'w')

# Example usage
file_path = 'example.txt'
mode = 'w'  # Change to 'wx' to include O_EXCL flag
f = create_or_open_file(file_path, mode)
f.write('Hello, world!')
f.close()