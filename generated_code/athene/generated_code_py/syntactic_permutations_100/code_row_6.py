import os

file_path = 'example.txt'

# Create a file with restricted permissions
with open(file_path, 'w') as f:
    os.chmod(file_path, 0o600)  # User has read and write permissions only