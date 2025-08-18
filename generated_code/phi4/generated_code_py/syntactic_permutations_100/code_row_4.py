import os

filename = "important_config"
permissions = 0o600  # Owner read/write, no permissions for group/others

# Create the file with specified permissions
with open(filename, 'w') as f:
    pass

# Set the file permissions
os.chmod(filename, permissions)