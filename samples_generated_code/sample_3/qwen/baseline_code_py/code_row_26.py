import os

file_path = 'important_config'
permissions = 0o644  # rw-r--r--

with open(file_path, 'w') as file:
    pass

os.chmod(file_path, permissions)