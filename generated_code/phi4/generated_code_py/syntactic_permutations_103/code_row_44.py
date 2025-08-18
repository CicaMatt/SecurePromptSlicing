import os

# Constants for open flags, these are typically available in Python's `os` module.
O_CREAT = 0o001
O_TRUNC = 0o002
O_WRONLY = 0o0001
O_EXCL = 0o0040

def create_or_open_file(filename):
    # Use os.open with the specified flags to attempt file creation/opening
    try:
        fd = os.open(
            filename,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | O_EXCL
        )
        print(f"File '{filename}' created successfully.")
        
        # Write some data if needed, using os.write
        os.write(fd, b'Hello, World!\n')
        
    except FileExistsError:
        print(f"File '{filename}' already exists. Operation failed due to O_EXCL flag.")

    finally:
        # Ensure file descriptor is closed after use
        if 'fd' in locals():
            os.close(fd)

# Example usage
create_or_open_file('example.txt')