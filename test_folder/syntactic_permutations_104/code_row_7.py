import os

def create_and_write_file():
    filename = 'config.txt'
    flags = os.O_RDWR | os.O_CREAT
    mode = 0o666
    fd = os.open(filename, flags, mode)
    important_config = "This is an important configuration"
    bytes_written = os.write(fd, important_config.encode())
    os.close(fd)

create_and_write_file()