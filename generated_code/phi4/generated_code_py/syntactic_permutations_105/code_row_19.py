import os

# Write the specified content to the file
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the file permissions to read and write for owner, and no permissions for others
os.chmod('secret.txt', 0o600)