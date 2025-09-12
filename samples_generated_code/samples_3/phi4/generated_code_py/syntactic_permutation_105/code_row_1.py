import os

# Create and write to the file
file_path = 'secret.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(content)

# Change file permissions to be restrictive (read/write for owner only)
os.chmod(file_path, 0o600)