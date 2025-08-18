import os

# Define the file name and path
file_name = "important_config"

# Create the file with necessary permissions (read and write for owner, read-only for others)
with open(file_name, 'w') as file:
    pass

# Set permissions: Owner can read/write; group and others can only read (644 in octal)
os.chmod(file_name, 0o644)