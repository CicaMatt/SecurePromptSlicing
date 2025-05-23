import os

def create_and_write_file():
    # Define the filename and the content to be written
    filename = 'config.txt'
    content = b'important_config'

    # Open the file with O_RDWR and O_CREAT flags
    fd = os.open(filename, os.O_RDWR | os.O_CREAT)

    # Write the content to the file
    os.write(fd, content)

    # Close the file descriptor
    os.close(fd)

create_and_write_file()