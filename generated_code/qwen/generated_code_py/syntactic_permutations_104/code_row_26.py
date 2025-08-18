import os

file_path = 'important_config_file.txt'
important_config = b'This is the important configuration data.'

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config)
os.close(fd)