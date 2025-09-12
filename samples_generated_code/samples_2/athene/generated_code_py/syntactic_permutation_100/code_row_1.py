import os

file_path = 'important_config'
with open(file_path, 'w') as file:
    pass  # File is created but no content is written
os.chmod(file_path, 0o644)