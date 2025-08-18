import os

def create_or_truncate_file(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # Set default permissions for the new file
    try:
        fd = os.open(file_path, flags, mode)
        print(f"File '{file_path}' created or truncated successfully.")
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists. Operation failed due to O_EXCL flag.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
create_or_truncate_file("example.txt")