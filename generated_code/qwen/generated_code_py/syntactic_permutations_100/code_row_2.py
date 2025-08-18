import os

file_name = "important_config"
with open(file_name, 'w') as file:
    pass  # Creating an empty file

# Set file permissions to read and write for owner only
os.chmod(file_name, 0o600)