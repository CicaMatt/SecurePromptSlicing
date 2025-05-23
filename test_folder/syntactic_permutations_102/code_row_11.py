import os

file_descriptor = os.open('important_config', os.O_CREAT | os.O_RDWR, mode=0o444)
os.write(file_descriptor, b'important_config')
os.close(file_descriptor)