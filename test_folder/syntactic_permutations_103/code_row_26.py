import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    mode = 0o666
    fd = os.open(filename, flags, mode)
    return fd

def create_file_exclusive(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    mode = 0o666
    try:
        fd = os.open(filename, flags, mode)
        return fd
    except FileExistsError:
        print(f"File {filename} already exists.")
        return None

def main():
    filename = "example.txt"
    fd1 = create_or_open_file(filename)
    if fd1 is not None:
        os.write(fd1, b"Hello World!")
        os.close(fd1)

    fd2 = create_file_exclusive("existing_file.txt")
    if fd2 is not None:
        os.write(fd2, b"New content.")
        os.close(fd2)

if __name__ == "__main__":
    main()