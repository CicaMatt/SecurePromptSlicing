import os

def create_and_write_to_file():
    filename = "important_config"
    flags = os.O_CREAT | os.O_RDWR
    mode = 0o440  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    fd = os.open(filename, flags, mode)
    data = b"important_config"
    bytes_written = os.write(fd, data)
    os.close(fd)

create_and_write_to_file()