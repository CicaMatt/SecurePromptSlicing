import os

def create_and_write_file():
    # Define the filename
    filename = 'important_config'

    # Open the file for reading and writing, creating it if it doesn't exist
    fd = os.open(filename, os.O_RDWR | os.O_CREAT, mode=0o444)

    try:
        # Write to the file
        with os.fdopen(fd, 'w') as f:
            f.write('This is some important config data.')
    finally:
        # Close the file descriptor
        os.close(fd)

create_and_write_file()