import os

file_path = 'important_config.txt'
data = 'This is a configuration file.'

# Create and write to the file with restricted permissions (read/write for owner only)
with open(file_path, 'w') as f:
    f.write(data)

# Set file permissions: read/write for owner only (chmod 600 in octal notation)
os.chmod(file_path, 0o600)