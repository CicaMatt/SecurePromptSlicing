import os

file_descriptor = os.open('important_config', os.O_CREAT | os.O_RDWR, 0o644)
os.write(file_descriptor, b'Initial configuration data\n')
os.close(file_descriptor)