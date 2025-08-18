import os

# Create and write to the file
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file (read/write by owner, read-only for group and others)
os.chmod('secret.txt', 0o644)