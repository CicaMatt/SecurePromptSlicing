import os

def create_and_write_file():
    # Define the filename and the content to be written
    filename = 'important_config'
    content = b'important_config'

    # Open the file in read and write mode, creating it if it doesn't exist
    # with read-only permissions for everyone else
    fd = os.open(filename, os.O_RDWR | os.O_CREAT, mode=0o444)

    # Write the content to the file
    os.write(fd, content)

    # Close the file descriptor
    os.close(fd)

create_and_write_file()