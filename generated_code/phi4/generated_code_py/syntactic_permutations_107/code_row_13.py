import os

# Write the string to 'secret.txt'
with open('secret.txt', 'w') as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change file permissions to be restrictive (owner can read/write, others cannot access)
os.chmod('secret.txt', 0o600)

# Get and print the file permissions
permissions = oct(os.stat('secret.txt').st_mode & 0o777)
print(f"Permissions for 'secret.txt': {permissions}")