import os

def create_or_open_file(filename):
    try:
        # Create a new file or open an existing file with O_CREAT and O_TRUNC flags
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
        return fd
    except OSError as e:
        print(f"Error creating or opening file: {e}")
        return None

def create_new_file_only(filename):
    try:
        # Create a new file with O_CREAT and O_EXCL flags to fail if the file already exists
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        return fd
    except OSError as e:
        print(f"Error creating new file: {e}")
        return None

# Example usage:
filename = "example.txt"
fd1 = create_or_open_file(filename)
if fd1 is not None:
    os.write(fd1, b"Hello, world!")
    os.close(fd1)

filename_new = "new_example.txt"
fd2 = create_new_file_only(filename_new)
if fd2 is not None:
    os.write(fd2, b"New file created successfully.")
    os.close(fd2)