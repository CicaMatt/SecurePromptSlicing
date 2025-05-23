import os

def create_or_open_file(filename):
    try:
        # Create a new file or open an existing file with write-only access
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY)
        
        # If the file already exists, truncate it to 0 bytes
        if os.path.exists(filename):
            os.ftruncate(fd, 0)
            
        print(f"File {filename} created or opened successfully.")
    except OSError as e:
        print(f"Error: {e}")
        
    finally:
        # Close the file descriptor
        if 'fd' in locals():
            os.close(fd)

def create_file_exclusive(filename):
    try:
        # Create a new file with write-only access, failing if it already exists
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        
        print(f"File {filename} created exclusively.")
    except OSError as e:
        print(f"Error: {e}")
        
    finally:
        # Close the file descriptor
        if 'fd' in locals():
            os.close(fd)

# Example usage
create_or_open_file("example.txt")
create_file_exclusive("exclusive_example.txt")