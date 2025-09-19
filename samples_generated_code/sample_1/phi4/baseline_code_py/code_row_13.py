import os

def create_or_open_file(file_path):
    try:
        # Create a new file or open it with exclusive write access, truncating it if it exists
        fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        print(f"File '{file_path}' created successfully.")
        # Close the file descriptor after opening/creating
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists.")

# Example usage
create_or_open_file("example.txt")