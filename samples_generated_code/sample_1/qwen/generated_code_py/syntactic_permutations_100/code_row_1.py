import os

file_name = "important_config"
with open(file_name, 'w') as file:
    pass  # Create an empty file

# Set file permissions to read and write for the owner only (0o600)
os.chmod(file_name, 0o600)