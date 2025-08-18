import os

def create_unique_file(file_path):
    try:
        # Open the file with flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
        fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        print(f"File created successfully at {file_path}")
        
        # Close the file descriptor
        os.close(fd)
    except FileExistsError:
        print(f"The file already exists at {file_path}")

# Example usage
create_unique_file("example.txt")