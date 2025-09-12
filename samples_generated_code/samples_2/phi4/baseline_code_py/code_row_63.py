import os

# Define the file path and name
file_path = 'important_config'

# Open (and create if not existing) the file with write permissions
with open(file_path, 'w') as f:
    pass  # Just to ensure it's created

# Set the necessary permissions: owner can read/write/execute; group and others can only read
os.chmod(file_path, 0o744)