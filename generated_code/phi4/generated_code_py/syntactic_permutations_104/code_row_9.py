import os

filename = "important_config.txt"
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644

file_descriptor = os.open(filename, mode, permissions)

os.write(file_descriptor, b"important_config")

os.close(file_descriptor)