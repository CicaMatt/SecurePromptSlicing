import os

file_path = 'important_config'
flags = os.O_RDWR | os.O_CREAT
mode = os.S_IRUSR | os.S_IWUSR | os.IROTH

fd = os.open(file_path, flags, mode)
os.write(fd, b'important_config')
os.close(fd)