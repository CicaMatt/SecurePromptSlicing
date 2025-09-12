import os

# Define the file path and name
file_path = "important_config"

# Open the file in write mode, create it if it doesn't exist
with open(file_path, 'w') as f:
    # Write content to the file (empty for now)
    pass

# Set necessary permissions: read/write for owner, read only for group and others
os.chmod(file_path, 0o644)  # Owner can read/write, others can only read