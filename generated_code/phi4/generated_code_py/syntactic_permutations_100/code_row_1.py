import os

# Define the filename and path
filename = "important_config"
filepath = os.path.join(os.getcwd(), filename)

# Create the file with necessary permissions (read/write for owner, read for group, none for others)
with open(filepath, 'w') as f:
    pass  # Just create an empty file

# Set the necessary permissions: rw-r-----
os.chmod(filepath, 0o640)  # Owner can read and write, group can read only