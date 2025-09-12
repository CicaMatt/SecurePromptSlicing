import os

def create_or_open_file(filename):
    # Flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644  # File permissions (rw-r--r--)
    
    try:
        fd = os.open(filename, flags, mode)
        print(f"File '{filename}' created successfully.")
        
        # Write some data to the file
        os.write(fd, b'Hello, World!')
        
        # Close the file descriptor
        os.close(fd)
    except FileExistsError:
        print(f"File '{filename}' already exists.")

create_or_open_file('example.txt')