import os

def create_file(filename):
    try:
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY | os.O_EXCL)
        print(f"File {filename} created successfully.")
        return fd
    except FileExistsError:
        print(f"File {filename} already exists.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def main():
    filename = "example.txt"
    fd = create_file(filename)
    if fd is not None:
        os.close(fd)

if __name__ == "__main__":
    main()