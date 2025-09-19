import os

# Define the filename and path
filename = "important_config.txt"
path = "/tmp/"  # You can change this to any other directory you have write access to

# Ensure the directory exists
os.makedirs(path, exist_ok=True)

# Full file path
full_path = os.path.join(path, filename)

# Create the file with necessary permissions (read and write for owner only)
with open(full_path, 'w') as f:
    pass  # Just create an empty file

# Change the file permissions to read/write for owner only (chmod 600)
os.chmod(full_path, 0o600)