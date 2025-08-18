import os

file_path = 'important_config'
with open(file_path, 'w') as f:
    pass  # Create an empty file
os.chmod(file_path, 0o644)  # Set permissions to rw-r--r--