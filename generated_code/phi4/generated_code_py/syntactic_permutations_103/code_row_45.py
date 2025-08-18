import os

def create_or_open_file(filename):
    # Use O_CREAT to ensure the file is created if it doesn't exist.
    # Use O_TRUNC to truncate the file to 0 bytes if it does exist.
    # Use O_WRONLY for writing only.
    # Use O_EXCL to fail if the file already exists, preventing overwriting.

    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # File permissions (owner read/write, group and others read)
    
    try:
        fd = os.open(filename, flags, mode)
        print(f"File '{filename}' opened for writing successfully.")
        
        # Close the file descriptor once done.
        os.close(fd)
    except FileExistsError:
        print(f"File '{filename}' already exists. O_EXCL flag triggered.")

# Example usage
create_or_open_file("example.txt")