import os

flags = os.O_CREAT | os.O_RDWR
mode = os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH
file_descriptor = os.open('important_config', flags, mode)

try:
    message = b'Initial configuration data\n'
    os.write(file_descriptor, message)
finally:
    os.close(file_descriptor)