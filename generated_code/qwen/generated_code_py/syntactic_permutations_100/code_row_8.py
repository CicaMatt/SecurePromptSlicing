import os

file_path = 'example_file.txt'

# Create a file with read and write permissions
with open(file_path, 'w') as file:
    pass

# Set file permissions to read and write for owner only
os.chmod(file_path, 0o600)