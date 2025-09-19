import os

file_path = 'important_config'
open_flags = os.O_RDWR | os.O_CREAT
permissions = 0o644  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH in octal

with open(file_path, open_flags, permissions) as file:
    file.write('important_config')