import os

# Constants for flags (using Python's built-in constants)
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

def create_or_open_file(file_path, mode='w'):
    # Open the file with specified flags and mode
    fd = os.open(
        file_path,
        O_WRONLY | O_CREAT | O_TRUNC | O_EXCL,
        0o644  # Set default permissions to rw-r--r--
    )
    
    try:
        # Perform operations on the file using the file descriptor
        with os.fdopen(fd, mode) as file:
            pass  # Add your file operations here (e.g., write data)
    except FileExistsError:
        print(f"File '{file_path}' already exists.")
    finally:
        # Ensure that the file is closed properly
        os.close(fd)

# Example usage
create_or_open_file('example.txt')