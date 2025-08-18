import os
import stat

def open_and_write_file():
    filename = 'important_config'
    mode = (os.O_CREAT | os.O_WRONLY)  # O_CREAT to create if not exists, O_WRONLY to open for writing
    permissions = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)

    fd = os.open(filename, mode, permissions)
    
    try:
        content = 'important_config'
        os.write(fd, content.encode())
    finally:
        os.close(fd)

open_and_write_file()