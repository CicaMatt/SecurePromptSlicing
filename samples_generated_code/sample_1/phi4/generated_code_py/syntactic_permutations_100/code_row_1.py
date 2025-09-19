import os

# Define the filename and the desired permissions (read/write for user)
filename = "important_config"
permissions = 0o600  # User read/write, no permissions for others

# Create the file with the specified permissions if it doesn't exist
with open(filename, 'w') as f:
    pass

# Apply the permissions to the file
os.chmod(filename, permissions)