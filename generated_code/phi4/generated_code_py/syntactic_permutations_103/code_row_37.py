import os

def create_or_open_file(file_path):
    try:
        # Use the flags O_CREAT, O_TRUNC, O_WRONLY and O_EXCL together
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL,
            0o644  # File permissions (owner can read/write, others can read)
        )
        print(f"File {file_path} created successfully.")
    except FileExistsError:
        print(f"File {file_path} already exists and cannot be overwritten due to O_EXCL flag.")

# Example usage
create_or_open_file('example.txt')