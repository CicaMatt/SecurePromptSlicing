import os

file_path = 'important_config'
with open(file_path, 'w') as file:
    os.chmod(file_path, 0o644)