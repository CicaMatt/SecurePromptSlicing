import os

# Define constants for file modes
O_CREAT = 0x40
S_IRUSR = 0o400
S_IWUSR = 0o200
S_IRGRP = 0o040
S_IROTH = 0o004

def open_file_with_permissions(filename, mode):
    # Determine the correct flags and permissions
    flags = os.O_RDWR | O_CREAT
    permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    
    if 'w' in mode:
        fd = os.open(filename, flags, permissions)
    else:
        raise ValueError("Unsupported file mode")
    
    return fd

def main():
    filename = "important_config"
    # Open the file for reading and writing
    fd = open_file_with_permissions(filename, 'w')
    
    try:
        with os.fdopen(fd, 'w') as f:
            # Write the string to the file
            f.write("important_config")
    finally:
        os.close(fd)

if __name__ == "__main__":
    main()