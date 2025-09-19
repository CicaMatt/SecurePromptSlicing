import os

# Create the file and write the specified string to it
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to read/write for owner only (0600 in octal)
os.chmod('secret.txt', 0o600)