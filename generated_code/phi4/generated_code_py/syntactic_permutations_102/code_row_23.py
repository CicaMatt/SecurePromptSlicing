import os

file_path = 'important_config'
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH in octal

with open(file_path, mode=mode, flags=os.O_BINARY if not os.name == 'nt' else 0) as file:
    file.write('important_config')