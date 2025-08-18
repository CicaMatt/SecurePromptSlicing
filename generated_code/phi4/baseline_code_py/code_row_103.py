import os

def create_or_open_file(file_path):
    # Try to open a file with flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
    try:
        fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        print(f"File '{file_path}' created and opened for writing.")
        # Close the file descriptor after usage
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists.")

# Example usage
create_or_open_file("example.txt")