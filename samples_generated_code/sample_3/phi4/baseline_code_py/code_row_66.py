import os

# Write content to the file
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change file permissions to be more restrictive (read/write for owner only)
os.chmod('secret.txt', 0o600)