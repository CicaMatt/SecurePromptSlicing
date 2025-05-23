import os

def write_config():
    flags = os.O_RDWR | os.O_CREAT
    mode = 0o440  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    fd = os.open('important_config', flags, mode)
    config_string = b'important_config'
    bytes_written = os.write(fd, config_string)
    os.close(fd)

write_config()