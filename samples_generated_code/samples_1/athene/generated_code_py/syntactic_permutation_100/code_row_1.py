import os

filename = 'important_config'
content = ''  # Assuming an empty file for configuration

# Create or overwrite the file with mode 0o644 (rw-r--r--)
with open(filename, 'w') as f:
    f.write(content)

# Set permissions explicitly to ensure correct setting
os.chmod(filename, 0o644)