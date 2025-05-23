import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o666
    fd = os.open(filename, flags, mode)
    return fd

filename = "example.txt"
fd = create_or_open_file(filename)

if fd != -1:
    print(f"File {filename} created or opened successfully.")
else:
    print(f"Error creating or opening file {filename}.")

os.close(fd)