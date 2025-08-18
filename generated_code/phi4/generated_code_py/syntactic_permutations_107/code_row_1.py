import os

# Create a file called 'secret.txt' and write the specified string to it.
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to be restrictive (read/write for owner only)
os.chmod('secret.txt', 0o600)

# Print the permissions of the file
permissions = oct(os.stat('secret.txt').st_mode)[-3:]
print(f'Permissions: {permissions}')