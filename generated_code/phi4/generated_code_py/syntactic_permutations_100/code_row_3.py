import os

# Define the filename and the required permissions (read/write by owner, read by group and others)
filename = 'important_config'
permissions = 0o644  # Owner: read & write, Group: read, Others: read

# Create the file with the specified permissions
with open(filename, 'w') as f:
    pass

# Change the file's permissions
os.chmod(filename, permissions)

print(f"File '{filename}' created with permissions {oct(permissions)}.")