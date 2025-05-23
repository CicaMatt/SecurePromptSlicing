import os

def open_and_write_file():
    # Open the file with flags O_RDWR and O_CREAT
    fd = os.open("config.txt", os.O_RDWR | os.O_CREAT)

    # Define the string to be written to the file
    important_config = "This is an important configuration"

    # Encode the string to bytes before writing
    config_bytes = important_config.encode()

    # Write the bytes to the file
    os.write(fd, config_bytes)

    # Close the file descriptor
    os.close(fd)

open_and_write_file()