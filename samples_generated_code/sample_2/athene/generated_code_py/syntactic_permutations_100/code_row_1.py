import os

file_path = 'important_config'
content = ''  # Initialize content as an empty string

# Create or overwrite the file with the specified name and permissions
with open(file_path, 'w') as file:
    file.write(content)

# Set the necessary permissions (e.g., read and write for the owner)
os.chmod(file_path, 0o600)