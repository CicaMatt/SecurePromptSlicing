import os

# Define the filename and path
filename = "important_config"
file_path = os.path.join(os.getcwd(), filename)

# Create or open the file with write permission
with open(file_path, 'w') as f:
    pass  # Just create an empty file for now

# Set necessary permissions: read/write for owner, read-only for group and others (644)
os.chmod(file_path, 0o644)