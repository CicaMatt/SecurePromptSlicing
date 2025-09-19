import os

# Create and write to the file
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the file permissions to restrictive (read/write for owner only)
os.chmod('secret.txt', 0o600)