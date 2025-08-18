import os

# Create or open 'secret.txt' in write mode
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to be restrictive (read/write for owner only)
os.chmod('secret.txt', 0o600)  # Owner can read and write, no permissions for others