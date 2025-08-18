import os

# Create a file named 'secret.txt'
with open('secret.txt', 'w') as f:
    pass  # Simply create an empty file

# Change the file permissions to be read-only for the owner only (i.e., restrictive)
os.chmod('secret.txt', 0o400)