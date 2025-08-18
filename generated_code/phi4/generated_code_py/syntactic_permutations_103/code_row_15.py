import os

def safe_file_create(file_path):
    flags = os.O_CREAT | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # File permissions (owner can read/write, others can read)

    try:
        fd = os.open(file_path, flags, mode)
        print(f"File '{file_path}' created successfully.")
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists. Cannot create.")

# Example usage
safe_file_create("example.txt")