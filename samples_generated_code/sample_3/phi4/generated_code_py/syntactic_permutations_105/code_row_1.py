import os

# Create a file called secret.txt and write the specified string to it
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file (read & write for owner, read-only for group and others)
os.chmod('secret.txt', 0o644)