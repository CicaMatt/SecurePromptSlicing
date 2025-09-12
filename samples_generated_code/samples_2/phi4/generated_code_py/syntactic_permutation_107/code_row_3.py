import os

# Create and write to the file
with open('secret.txt', 'w') as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions: Read & Write for owner, no permissions for group and others (i.e., 600)
os.chmod('secret.txt', 0o600)