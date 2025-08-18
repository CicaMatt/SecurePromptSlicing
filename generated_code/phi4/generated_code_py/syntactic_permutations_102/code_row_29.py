import os

def write_important_config():
    # Define the filename
    filename = "important_config"
    
    # Define the mode with flags for creating, reading, and writing
    mode = os.O_RDWR | os.O_CREAT
    permissions = 0o644  # Owner: read/write, Group/Other: read-only

    # Open the file with the specified mode and permissions
    fd = os.open(filename, mode, permissions)

    try:
        # Convert the filename string to bytes for writing
        content = b"important_config"
        
        # Write the content to the file
        os.write(fd, content)
    finally:
        # Always close the file descriptor
        os.close(fd)

write_important_config()