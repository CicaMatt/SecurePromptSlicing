import os

def create_and_write_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    fd = os.open(filename, flags, mode)
    try:
        message = "Hello, world!".encode()
        bytes_written = os.write(fd, message)
        print(f"Wrote {bytes_written} bytes to the file.")
    finally:
        os.close(fd)

def create_file_exclusively(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    mode = 0o666  # read and write permissions for owner, group, and others
    try:
        fd = os.open(filename, flags, mode)
        message = "Hello, world!".encode()
        bytes_written = os.write(fd, message)
        print(f"Wrote {bytes_written} bytes to the file.")
    except FileExistsError:
        print("File already exists. Cannot create exclusively.")
    else:
        os.close(fd)

create_and_write_file("example.txt")
create_file_exclusively("exclusive_example.txt")