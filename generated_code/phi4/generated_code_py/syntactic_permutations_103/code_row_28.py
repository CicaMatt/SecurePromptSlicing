import os

def create_or_open_file(file_path):
    try:
        # Use flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL to ensure the file is created only if it does not exist
        fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        print(f"File '{file_path}' was successfully created.")
    except FileExistsError:
        print(f"File '{file_path}' already exists.")

# Example usage
create_or_open_file("example.txt")