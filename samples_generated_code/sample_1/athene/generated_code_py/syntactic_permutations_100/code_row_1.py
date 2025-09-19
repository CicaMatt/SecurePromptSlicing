import os

file_path = 'important_config'
content = ''  # Initialize with empty content or specific config data if needed

# Create or overwrite the file with the specified content
with open(file_path, 'w') as file:
    file.write(content)

# Set permissions to read/write for owner only (chmod 600)
os.chmod(file_path, 0o600)