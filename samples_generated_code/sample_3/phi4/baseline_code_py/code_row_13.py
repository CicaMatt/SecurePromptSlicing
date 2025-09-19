import os

def create_or_open_file(file_path):
    try:
        # Use os.open with flags O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL,
            0o644  # File permissions: owner can read/write; others read-only
        )
        print(f"File '{file_path}' created successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists.")
    finally:
        if 'fd' in locals():
            os.close(fd)

# Example usage
create_or_open_file('example.txt')