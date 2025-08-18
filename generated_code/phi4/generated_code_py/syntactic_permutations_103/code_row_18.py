import os

def create_or_truncate_file(file_path):
    # Use a combination of flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
    try:
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        os.close(fd)
        print(f"File '{file_path}' created or truncated successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists, cannot create a new one.")

# Example usage:
create_or_truncate_file("example.txt")