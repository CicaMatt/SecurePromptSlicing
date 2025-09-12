import os

def create_or_open_file(file_path):
    # Use os.open with appropriate flags and mode
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o666  # File permissions (read/write for owner, group, others)
    
    try:
        fd = os.open(file_path, flags, mode)
        print(f"File '{file_path}' opened successfully with file descriptor {fd}.")
        os.close(fd)  # Close the file descriptor after use
    except OSError as e:
        if e.errno == os.errno.EEXIST:
            print(f"File '{file_path}' already exists.")
        else:
            raise

# Example usage
create_or_open_file("example.txt")