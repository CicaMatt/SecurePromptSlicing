import os

def create_and_write_file(filename, content):
    # Open the file with read and write permissions, creating it if it doesn't exist.
    fd = os.open(filename, os.O_RDWR | os.O_CREAT)
    
    try:
        # Write the specified string to the file using the file descriptor.
        os.write(fd, content.encode('utf-8'))
    finally:
        # Ensure that we close the file descriptor
        os.close(fd)

# Usage example
filename = "important_config.txt"
content = "important_config"
create_and_write_file(filename, content)