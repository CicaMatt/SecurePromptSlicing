import os

def create_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        print(f"File {filename} created successfully")
        os.close(fd)
    except FileExistsError:
        print(f"File {filename} already exists")

def main():
    filename = "example.txt"
    create_file(filename)

if __name__ == "__main__":
    main()