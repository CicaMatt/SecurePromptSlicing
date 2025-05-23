import os

def create_and_write_file():
    # Open the file for reading and writing, creating it if it doesn't exist
    # with read permissions for the owner and group, and read-only permissions for others
    fd = os.open("important_config", os.O_RDWR | os.O_CREAT, mode=0o444)

    # Write the string "important_config" to the file
    os.write(fd, b"important_config")

    # Close the file descriptor
    os.close(fd)

create_and_write_file()