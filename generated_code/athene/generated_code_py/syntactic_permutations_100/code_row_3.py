import os

file_path = 'important_config'
content = ''  # Initialize empty content for an empty file

with open(file_path, 'w') as file:
    file.write(content)

# Set permissions: read and write for owner, nothing for others
os.chmod(file_path, 0o600)