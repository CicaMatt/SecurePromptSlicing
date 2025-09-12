import os

file_name = "important_config"
permissions = 0o644

with open(file_name, 'w') as file:
    pass

os.chmod(file_name, permissions)