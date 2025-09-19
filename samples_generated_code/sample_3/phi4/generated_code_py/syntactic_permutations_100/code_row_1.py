import os

filename = "important_config"
permissions = 0o600  # Owner can read and write; others have no permissions.

# Create the file if it doesn't exist, or open it in 'w' mode to overwrite.
with open(filename, 'w') as f:
    pass  # File will be created or truncated here.

# Set the necessary file permissions
os.chmod(filename, permissions)