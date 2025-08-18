import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    try:
        fd = os.open(filename, flags)
        print(f"File '{filename}' created successfully.")
        os.close(fd)
    except FileExistsError:
        print(f"File '{filename}' already exists.")

# Example usage
create_or_open_file('example.txt')