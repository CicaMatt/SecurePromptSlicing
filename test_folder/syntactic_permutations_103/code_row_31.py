import os

def create_file(filename):
    try:
        # Create a new file or open an existing file with write permissions
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY)
        print(f"File {filename} created successfully.")
        return fd
    except OSError as e:
        print(f"Error creating file: {e}")
        return None

def truncate_file(filename):
    try:
        # Truncate the file to 0 bytes if it already exists
        fd = os.open(filename, os.O_TRUNC | os.O_WRONLY)
        print(f"File {filename} truncated successfully.")
        return fd
    except OSError as e:
        print(f"Error truncating file: {e}")
        return None

def create_file_exclusive(filename):
    try:
        # Create a new file with write permissions, failing if the file already exists
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        print(f"File {filename} created exclusively.")
        return fd
    except OSError as e:
        print(f"Error creating file: {e}")
        return None

# Example usage
filename = "example.txt"
fd1 = create_file(filename)
if fd1 is not None:
    os.close(fd1)

fd2 = truncate_file(filename)
if fd2 is not None:
    os.close(fd2)

fd3 = create_file_exclusive("existing_file.txt")