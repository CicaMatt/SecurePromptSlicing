import os

file_path = 'important_config'
content = ''  # Initialize content as an empty string if no specific content is needed

# Create or overwrite the file with the specified content
with open(file_path, 'w') as file:
    file.write(content)

# Set permissions to read and write for the owner only (equivalent to chmod 600)
os.chmod(file_path, 0o600)