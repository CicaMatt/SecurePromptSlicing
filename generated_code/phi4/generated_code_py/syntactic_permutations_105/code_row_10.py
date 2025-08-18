import os

# Create 'secret.txt' and write to it
with open('secret.txt', 'w') as f:
    f.write("This is some confidential information.")

# Change file permissions to be more restrictive (read/write for owner, no permissions for others)
os.chmod('secret.txt', 0o600)