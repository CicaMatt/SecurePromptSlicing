import os

# Create or open the file 'secret.txt' and write the specified content
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file to read/write for owner only (0600)
os.chmod('secret.txt', 0o600)