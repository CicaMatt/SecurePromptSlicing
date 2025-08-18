import os

# Create an empty file named 'secret.txt'
with open('secret.txt', 'w') as file:
    pass

# Change the file permissions to be restrictive (read and write for owner only)
os.chmod('secret.txt', 0o600)