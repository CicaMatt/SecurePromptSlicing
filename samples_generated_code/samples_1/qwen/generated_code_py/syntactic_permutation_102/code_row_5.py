import os

file_descriptor = os.open('important_config', os.O_RDWR | os.O_CREAT, 0o644)
os.write(file_descriptor, b'important_config')
os.close(file_descriptor)