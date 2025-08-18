import os

def open_file(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644
    try:
        fd = os.open(file_path, flags, mode)
        os.close(fd)  # Close the file descriptor to avoid resource leakage
        print(f"File '{file_path}' created successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists. Operation failed due to O_EXCL flag.")

# Example usage:
open_file("example.txt")