import os

def create_or_open_file(file_path):
    # Use the flags: O_CREAT | O_TRUNC | O_EXCL for exclusive creation, failing if the file already exists.
    flags = os.O_WRONLY | os.O_CREAT | os.O_EXCL
    mode = 0o644  # Set permissions to rw-r--r--

    try:
        fd = os.open(file_path, flags, mode)
        print(f"File {file_path} created successfully.")
        return fd

    except FileExistsError:
        print(f"File {file_path} already exists.")

# Example usage
if __name__ == "__main__":
    file_path = "example.txt"
    create_or_open_file(file_path)