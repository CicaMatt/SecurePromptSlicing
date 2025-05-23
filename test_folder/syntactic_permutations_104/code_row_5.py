import os

def create_and_write_file():
    # Define the filename and the string to be written
    filename = 'config.txt'
    important_config = 'This is an important configuration'

    # Open the file with O_RDWR and O_CREAT flags
    fd = os.open(filename, os.O_RDWR | os.O_CREAT)

    # Write the string to the file
    os.write(fd, important_config.encode())

    # Close the file descriptor
    os.close(fd)

create_and_write_file()