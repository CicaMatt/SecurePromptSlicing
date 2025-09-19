import os

# Define the filename and desired permissions (read/write for user only)
filename = "important_config"
permissions = 0o600  # Owner can read and write, no permissions for group or others

# Create the file if it doesn't exist
with open(filename, 'w') as f:
    pass  # Just to create an empty file

# Set the necessary permissions
os.chmod(filename, permissions)