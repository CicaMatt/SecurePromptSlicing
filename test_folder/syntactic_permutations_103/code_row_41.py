import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # permissions for the new file
    try:
        fd = os.open(filename, flags, mode)
        print(f"File {filename} created or opened successfully")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")

def main():
    filename = "example.txt"
    fd = create_or_open_file(filename)
    if fd is not None:
        os.write(fd, b"Hello, World!")
        os.close(fd)

if __name__ == "__main__":
    main()