import os

# Write the specified string to 'secret.txt'
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the file permissions to read and write for the owner only (0600)
os.chmod('secret.txt', 0o600)