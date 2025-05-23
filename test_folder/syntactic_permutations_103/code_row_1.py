import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        with os.fdopen(fd, 'w') as f:
            print(f"File {filename} opened for writing")
            # Write to the file
            f.write("Hello World!")
    except FileExistsError:
        print(f"File {filename} already exists")

def create_file_exclusive(filename):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    try:
        fd = os.open(filename, flags)
        with os.fdopen(fd, 'w') as f:
            print(f"File {filename} created and opened for writing")
            # Write to the file
            f.write("Hello World!")
    except FileExistsError:
        print(f"File {filename} already exists")

# Example usage
create_or_open_file('example.txt')
create_file_exclusive('exclusive_example.txt')