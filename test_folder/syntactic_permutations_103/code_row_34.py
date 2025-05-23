import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    return os.open(filename, flags)

def create_file_if_not_exists(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    try:
        return os.open(filename, flags)
    except FileExistsError:
        print(f"File {filename} already exists.")

# Example usage
filename = "example.txt"
file_descriptor = create_or_open_file(filename)
print(f"File descriptor: {file_descriptor}")
os.close(file_descriptor)

create_file_if_not_exists("example2.txt")