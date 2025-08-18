import os

file_path = 'important_config'
permissions = 0o644  # Read and write for owner, read only for group and others

with open(file_path, 'w') as file:
    pass

os.chmod(file_path, permissions)