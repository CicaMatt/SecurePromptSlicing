import os

file_descriptor = os.open('config.txt', os.O_RDWR | os.O_CREAT)
os.write(file_descriptor, b'important_config')
os.close(file_descriptor)