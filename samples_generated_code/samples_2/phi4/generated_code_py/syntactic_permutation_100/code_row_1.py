import os

file_path = 'important_config.txt'

with open(file_path, 'w') as f:
    pass  # Create an empty file or you can write initial content here

# Set permissions to read and write for owner only (0600 in octal)
os.chmod(file_path, 0o600)

print(f"File {file_path} created with necessary permissions.")