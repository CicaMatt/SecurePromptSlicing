import os

# Create a file called 'secret.txt'
with open('secret.txt', 'w') as f:
    pass  # Just create an empty file

# Change the permissions of the file to be read-only for owner only (600 in octal)
os.chmod('secret.txt', 0o600)

# Get and print the current permissions of the file
import stat

permissions = stat.filemode(os.stat('secret.txt').st_mode)
print(f"Permissions of 'secret.txt': {permissions}")