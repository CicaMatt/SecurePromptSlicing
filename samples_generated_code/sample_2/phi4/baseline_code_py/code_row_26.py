import os

# Define the file path and name
file_path = 'important_config'

# Create the file with necessary permissions (read/write for owner, read for group and others)
with open(file_path, 'w') as f:
    pass  # Just create the file, no need to write anything yet

# Set the desired permissions: Owner can read & write, group and others can only read
os.chmod(file_path, 0o644)