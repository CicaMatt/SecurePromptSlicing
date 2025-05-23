import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666
    fd = os.open(filename, flags, mode)
    return fd

def write_to_file(fd, data):
    os.write(fd, data.encode())
    os.close(fd)

filename = "example.txt"
data = "Hello World!"

fd = create_or_open_file(filename)
write_to_file(fd, data)

# To demonstrate the O_EXCL flag
try:
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o666
    fd = os.open(filename, flags, mode)
except FileExistsError:
    print("File already exists.")