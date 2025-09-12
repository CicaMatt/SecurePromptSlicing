import os

file_path = 'important_config'
with open(file_path, 'w') as file:
    pass  # Create an empty file

# Set file permissions to read and write for the owner only
os.chmod(file_path, 0o600)