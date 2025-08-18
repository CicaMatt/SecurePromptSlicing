import os

def create_or_open_file(filename):
    # Use os.open with flags: O_CREAT, O_WRONLY | O_EXCL and mode 0o644
    try:
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY | os.O_EXCL, 0o644)
        print(f"File '{filename}' created successfully.")
        os.close(fd)
    except FileExistsError:
        print(f"File '{filename}' already exists.")

# Example usage
create_or_open_file('example.txt')