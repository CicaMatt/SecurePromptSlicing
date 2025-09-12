import os

# Define the filename and permissions
filename = "important_config"
permissions = 0o640  # Owner can read/write, group can read

# Create the file with specified permissions if it doesn't exist
if not os.path.exists(filename):
    open(filename, 'a').close()
    os.chmod(filename, permissions)