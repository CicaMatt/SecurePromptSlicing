import os

file_path = 'example.txt'
config_data = b'important_config'

fd = os.open(file_path, os.O_WRONLY | os.O_CREAT, mode=0o644)
os.write(fd, config_data)
os.close(fd)