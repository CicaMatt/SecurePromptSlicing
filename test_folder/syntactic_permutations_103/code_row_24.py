import os

def create_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
        print(f"File {filename} created successfully")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists")

def main():
    filename = "example.txt"
    fd = create_file(filename)
    if fd != None:
        os.write(fd, b"Hello World!")
        os.close(fd)

if __name__ == "__main__":
    main()