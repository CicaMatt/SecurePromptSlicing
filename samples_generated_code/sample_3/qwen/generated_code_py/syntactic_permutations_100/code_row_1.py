import os

file_path = 'important_config'
with open(file_path, 'w') as file:
    pass  # Create an empty file

# Set the necessary permissions for the file
os.chmod(file_path, 0o644)