import os

file_path = 'important_config'
with open(file_path, 'w') as file:
    pass

# Set file permissions to read and write for owner only (0o600)
os.chmod(file_path, 0o600)