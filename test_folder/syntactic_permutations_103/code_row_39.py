import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # default permissions
    fd = os.open(filename, flags, mode)
    return fd

filename = "example.txt"
try:
    fd = create_or_open_file(filename)
    print(f"File {filename} opened or created successfully")
except FileExistsError:
    print(f"File {filename} already exists")

def write_to_file(fd):
    message = b"Hello, World!"
    bytes_written = os.write(fd, message)
    return bytes_written

bytes_written = write_to_file(fd)
print(f"Wrote {bytes_written} bytes to the file")

os.close(fd)

with open(filename, 'rb') as f:
    content = f.read()
    print(content.decode())