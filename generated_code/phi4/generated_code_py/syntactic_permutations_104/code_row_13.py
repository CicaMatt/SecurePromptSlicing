import os

def write_important_config(file_path, data):
    # Open a file with read/write permissions, create if it doesn't exist
    fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
    
    try:
        # Write data to the file descriptor
        os.write(fd, data.encode())
    finally:
        # Ensure that the file is closed properly
        os.close(fd)

# Usage example
file_path = 'example_file.txt'
important_config = 'This is important configuration data.'
write_important_config(file_path, important_config)